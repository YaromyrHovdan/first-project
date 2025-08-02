// Компилировать: g++ -std=c++20 main.cpp -O2 -Wall -o main
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <cmath>
#include <compare>
#include <sstream>
#include <type_traits>

// ---------------- Vec3: 3D-вектор с операциями ----------------
struct Vec3 {
    double x = 0, y = 0, z = 0;

    constexpr Vec3() = default;
    constexpr Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    // Автоматическое сравнение (C++20)
    auto operator<=>(const Vec3&) const = default;

    constexpr double length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    constexpr Vec3 normalized() const {
        double len = length();
        if (len == 0) return {0,0,0};
        return {x/len, y/len, z/len};
    }

    constexpr double dot(const Vec3& o) const {
        return x*o.x + y*o.y + z*o.z;
    }

    constexpr Vec3 cross(const Vec3& o) const {
        return {
            y*o.z - z*o.y,
            z*o.x - x*o.z,
            x*o.y - y*o.x
        };
    }

    constexpr Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    constexpr Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    constexpr Vec3 operator*(double s) const { return {x*s, y*s, z*s}; }
    constexpr Vec3 operator/(double s) const { return {x/s, y/s, z/s}; }

    Vec3& operator+=(const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vec3& operator-=(const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }

    std::string to_string() const {
        std::ostringstream os;
        os << "Vec3(" << x << ", " << y << ", " << z << ")";
        return os.str();
    }
};

// ---------------- Color с битовыми полями ----------------
// Упаковка RGBA в 32-бита с доступом к цвету и нормализованными каналами
struct Color {
    // по умолчанию: little-endian порядок полей не гарантирован в стандарте, 
    // но мы используем unsigned для битовых полей как пример
    unsigned r : 8;
    unsigned g : 8;
    unsigned b : 8;
    unsigned a : 8;

    constexpr Color(unsigned red, unsigned green, unsigned blue, unsigned alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    // Создать из hex: 0xRRGGBBAA или 0xRRGGBB
    static constexpr Color from_hex(unsigned hex) {
        if (hex <= 0xFFFFFF) { // без альфы
            return Color((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF, 255);
        } else {
            return Color((hex >> 24) & 0xFF, (hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
        }
    }

    constexpr double rf() const { return r / 255.0; }
    constexpr double gf() const { return g / 255.0; }
    constexpr double bf() const { return b / 255.0; }
    constexpr double af() const { return a / 255.0; }

    std::string to_string() const {
        std::ostringstream os;
        os << "Color(r=" << r << ", g=" << g << ", b=" << b << ", a=" << a << ")";
        return os.str();
    }
};

// ---------------- Преобразование (Transform) ----------------
// Простая иерархическая трансформация: позиция, вращение (в градусах, только Z для простоты), масштаб
struct Transform {
    Vec3 position{0,0,0};
    Vec3 rotation{0,0,0}; // Euler в градусах (x=поворот вокруг X и т.п.)
    Vec3 scale{1,1,1};

    // Получить 4x4 матрицу в виде строки (упрощённо, только для демонстрации)
    std::string to_string() const {
        std::ostringstream os;
        os << "Transform(pos=" << position.to_string()
           << ", rot=" << rotation.to_string()
           << ", scale=" << scale.to_string() << ")";
        return os.str();
    }

    // Комбинирование: применить другой трансформ как дочерний
    Transform combine(const Transform& child) const {
        // Упрощённо: комбинируем масштаб, позицию и добавляем вращение по Z только
        Transform result;
        result.scale = { scale.x * child.scale.x, scale.y * child.scale.y, scale.z * child.scale.z };
        result.position = position + child.position; // без учёта вращения для простоты
        result.rotation = rotation + child.rotation;
        return result;
    }
};

// ---------------- SceneNode: иерархия узлов ----------------
struct SceneNode {
    std::string name;
    Transform transform;
    std::vector<std::shared_ptr<SceneNode>> children;

    SceneNode(std::string_view n) : name(n) {}

    void add_child(std::shared_ptr<SceneNode> child) {
        children.push_back(std::move(child));
    }

    // Рекурсивный обход с накоплением глобальной трансформации
    void traverse(const Transform& parentTransform = {}) const {
        Transform global = parentTransform.combine(transform);
        std::cout << "Node: " << name << " | Global: " << global.to_string() << "\n";
        for (const auto& ch : children) {
            ch->traverse(global);
        }
    }

    // Простой JSON-подобный сериализатор (рекурсивно)
    std::string serialize(int indent = 0) const {
        std::string pad(indent, ' ');
        std::ostringstream os;
        os << pad << "{\n";
        os << pad << "  \"name\": \"" << name << "\",\n";
        os << pad << "  \"transform\": \"" << transform.to_string() << "\",\n";
        os << pad << "  \"children\": [\n";
        for (size_t i = 0; i < children.size(); ++i) {
            os << children[i]->serialize(indent + 4);
            if (i + 1 < children.size()) os << ",\n";
            else os << "\n";
        }
        os << pad << "  ]\n";
        os << pad << "}";
        return os.str();
    }
};

// ---------------- Shape: tagged union через std::variant ----------------
struct Circle { double radius; };
struct Rectangle { double width, height; };

struct Shape {
    std::variant<Circle, Rectangle> data;

    double area() const {
        return std::visit([](const auto& v) -> double {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, Circle>)
                return M_PI * v.radius * v.radius;
            else if constexpr (std::is_same_v<T, Rectangle>)
                return v.width * v.height;
            else
                return 0.0;
        }, data);
    }

    std::string describe() const {
        return std::visit([](const auto& v)->std::string {
            using T = std::decay_t<decltype(v)>;
            std::ostringstream os;
            if constexpr (std::is_same_v<T, Circle>)
                os << "Circle(radius=" << v.radius << ")";
            else if constexpr (std::is_same_v<T, Rectangle>)
                os << "Rectangle(w=" << v.width << ", h=" << v.height << ")";
            return os.str();
        }, data);
    }
};

// ---------------- Шаблонная матрица с ограничением (concept) ----------------
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T, size_t Rows, size_t Cols>
struct Matrix {
    static_assert(Rows > 0 && Cols > 0);
    T data[Rows][Cols]{};

    constexpr T& at(size_t r, size_t c) {
        return data[r][c];
    }

    constexpr const T& at(size_t r, size_t c) const {
        return data[r][c];
    }

    // Простой вывод
    std::string to_string() const {
        std::ostringstream os;
        os << "Matrix<" << Rows << "x" << Cols << ">{";
        for (size_t i = 0; i < Rows; ++i) {
            os << "[";
            for (size_t j = 0; j < Cols; ++j) {
                os << data[i][j];
                if (j+1 < Cols) os << ", ";
            }
            os << "]";
            if (i+1 < Rows) os << ", ";
        }
        os << "}";
        return os.str();
    }

    // Умножение на вектор (Cols должно совпадать с размером вектора)
    template<size_t Other>
    requires (Cols == Other)
    constexpr Matrix<T, Rows, Other> operator*(const Matrix<T, Cols, Other>& rhs) const {
        Matrix<T, Rows, Other> result{};
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Other; ++j) {
                T sum = T{};
                for (size_t k = 0; k < Cols; ++k) {
                    sum += data[i][k] * rhs.data[k][j];
                }
                result.at(i,j) = sum;
            }
        }
        return result;
    }
};

// ---------------- main: демонстрация ----------------
int main() {
    std::cout << "=== Vec3 пример ===\n";
    Vec3 a{1,2,3};
    Vec3 b{4,5,6};
    std::cout << a.to_string() << " + " << b.to_string() << " = " << (a + b).to_string() << "\n";
    std::cout << "dot(a,b) = " << a.dot(b) << ", cross(a,b) = " << a.cross(b).to_string() << "\n";

    std::cout << "\n=== Color пример ===\n";
    constexpr Color red = Color::from_hex(0xFF0000);
    constexpr Color semi = Color::from_hex(0x11223344);
    std::cout << red.to_string() << " -> normalized: (" << red.rf() << ", " << red.gf() << ", " << red.bf() << ")\n";
    std::cout << semi.to_string() << " alpha float = " << semi.af() << "\n";

    std::cout << "\n=== Shape (variant) ===\n";
    Shape c{Circle{2.0}};
    Shape r{Rectangle{3.0, 4.0}};
    std::cout << c.describe() << " area = " << c.area() << "\n";
    std::cout << r.describe() << " area = " << r.area() << "\n";

    std::cout << "\n=== Scene Graph ===\n";
    auto root = std::make_shared<SceneNode>("root");
    root->transform.position = {0,0,0};
    auto child1 = std::make_shared<SceneNode>("child1");
    child1->transform.position = {1,0,0};
    child1->transform.rotation = {0,45,0};
    auto child2 = std::make_shared<SceneNode>("child2");
    child2->transform.position = {0,2,0};
    root->add_child(child1);
    child1->add_child(child2);
    root->traverse();
    std::cout << "\nSerialized scene:\n" << root->serialize() << "\n";

    std::cout << "\n=== Matrix (шаблон) ===\n";
    Matrix<double,2,2> m1;
    m1.at(0,0) = 1; m1.at(0,1) = 2;
    m1.at(1,0) = 3; m1.at(1,1) = 4;
    Matrix<double,2,2> m2;
    m2.at(0,0) = 5; m2.at(0,1) = 6;
    m2.at(1,0) = 7; m2.at(1,1) = 8;
    auto prod = m1 * m2;
    std::cout << m1.to_string() << " * " << m2.to_string() << " = " << prod.to_string() << "\n";

    return 0;
}
