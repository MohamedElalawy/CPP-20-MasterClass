#include <iostream>

// ---------- constexpr ----------

// A constexpr function: can be evaluated at compile time if the argument is constant.
constexpr int square(int x) { return x * x; }

// A constexpr variable: must be initialized with a constant expression.
constexpr int kGrid = 4;

// ---------- constinit ----------

// constinit requires a compile-time constant initializer,
// but the variable itself is not const → it can be modified at runtime.
// It ensures "no dynamic initialization" → avoids static initialization order issues.
constexpr int kBaseId = 100;              // a constexpr helper
constinit int g_nextId = kBaseId + 1;     // initialized at compile time, mutable later
constinit const char* g_appName = "DemoApp"; // pointer is initialized at compile time

// ---------- static_assert ----------

// Compile-time assertion: checks that square(5) == 25 at compile time.
// If false, the program won't compile.
static_assert(square(5) == 25, "square must be correct");

// kArea is computed at compile time using a constexpr function.
constexpr int kArea = square(kGrid);

// Another compile-time assertion: ensures area of 4x4 grid = 16.
static_assert(kArea == 16, "Area must be 16 for a 4x4 grid");

// ---------- constexpr class ----------

// User-defined type with constexpr constructor and method.
struct Point {
    int x, y;

    // constexpr constructor → can be used to create compile-time objects
    constexpr Point(int a, int b) : x(a), y(b) {}

    // constexpr method: can be evaluated at compile time
    constexpr int manhattan() const {
        return (x < 0 ? -x : x) + (y < 0 ? -y : y);
    }
};

// Compile-time check: manhattan distance of (3,-4) must be 7.
static_assert(Point(3, -4).manhattan() == 7, "Manhattan distance must be 7");

int main() {
    int r = 7;

    // square(r) evaluated at runtime because 'r' is not constexpr
    std::cout << "square(" << r << ") = " << square(r) << '\n';

    // Compile-time object: p is constructed entirely at compile time
    constexpr Point p{3, -4};
    std::cout << "Point manhattan distance: " << p.manhattan() << '\n';

    // constinit globals are guaranteed to be initialized before main()
    std::cout << "App: " << g_appName << ", nextId(before) = " << g_nextId << '\n';

    // constinit variables are not const → they can be changed
    g_nextId += 10;
    std::cout << "nextId(after) = " << g_nextId << '\n';

    // Using constexpr values in array bounds
    int grid[kGrid * kGrid] = {}; // size = 16, known at compile time
    std::cout << "Grid has " << std::size(grid)
              << " cells (kArea = " << kArea << ")\n";

    return 0;
}
