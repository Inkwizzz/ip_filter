#include <iostream>
#include <cstdint>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>
#include <string>

//Check if container
template<typename T>
struct is_container {
private:
    template<typename U>
    static auto test(int) -> decltype(
        std::declval<U>().begin(),
        std::declval<U>().end(),
        std::true_type{}
        );

    template<typename>
    static std::false_type test(...);

public:
    static constexpr bool value =
        decltype(test<T>(0))::value &&
        !std::is_convertible_v<T, std::string>;
};

//SFINAE for containers
template<typename T>
std::enable_if_t<is_container<T>::value>
print_ip(const T& container) {
    auto it = container.begin();
    if (it != container.end()) {
        std::cout << *it;
        ++it;
    }
    for (; it != container.end(); ++it) {
        std::cout << "." << *it;
    }
    std::cout << std::endl;
}

//SFINAE for ints
template<typename T,
    typename std::enable_if<std::is_integral<T>::value
    >::type* = nullptr 
>
void print_ip(T value) {
    const auto* byte_ptr = reinterpret_cast<const uint8_t*>(&value);
    std::string string;

    for (size_t i = 0; i < sizeof(T); ++i) {
        if (i != 0) string += ".";
        string += std::to_string(static_cast<int>(byte_ptr[sizeof(T) - 1 - i]));
    }

    std::cout << string << std::endl;
}

//SFINAE for strings
template <typename T,
    typename std::enable_if<std::is_convertible<T,
    std::string>::value>::type* = nullptr>
void print_ip(T value) {

    std::cout << value << std::endl;
}

//Check for tuples
template<typename... Args>
struct all_same_types : std::true_type {};

template<typename T1, typename T2, typename... Rest>
struct all_same_types<T1, T2, Rest...>
    : std::conditional<
    std::is_same<T1, T2>::value,
    all_same_types<T2, Rest...>,
    std::false_type
    >::type {};

//print func for tuples
template<size_t I = 0, typename... Args>
inline typename std::enable_if<I == sizeof...(Args), void>::type
print_tuple(const std::tuple<Args...>&) {}
//print for tuples
template<size_t I = 0, typename... Args>
inline typename std::enable_if < I < sizeof...(Args), void>::type
    print_tuple(const std::tuple<Args...>& t) {
    if (I != 0) std::cout << ".";
    std::cout << std::get<I>(t);
    print_tuple<I + 1>(t);
}
//SFINAE for tuples
template<typename... Args>
void print_ip(const std::tuple<Args...>& t) {
    static_assert(all_same_types<Args...>::value,
        "All tuple elements must be of the same type");
    print_tuple(t);
    std::cout << std::endl;
}

int main() {

    print_ip(int8_t{ -1 });
    print_ip(int16_t{ 0 });
    print_ip(int32_t{ 2130706433 });
    print_ip(int64_t{ 8875824491850138409 });
    print_ip(std::string{ "Hello, World!" });
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});
    print_ip(std::make_tuple(123, 456, 789, 0));

    return 0;
}