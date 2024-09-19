#include <iostream>
#include <vector>

std::istream& operator >> (std::istream& is, std::vector<int>& v) {
    for (auto& a : v) {
        is >> a;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const std::vector<int>& v) {
    for (const auto& a : v) {
        os << a << ' ';
    }
    return os;
}

int count = 0;

std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> res (a.size() + b.size());
    size_t i = 0, j = 0, k = 0;
    while (i < a.size() || j < b.size()) {
        if (i == a.size()) {
            res[k] = b[j];
            ++k, ++j;
        } else if (j == b.size()) {
            res[k] = a[i];
            ++k, ++i;
        } else if (a[i] <= b[j]) {
            res[k] = a[i];
            ++k, ++i;
        } else {
            count += a.size() - i;
            res[k] = b[j];
            ++k, ++j;
        }
    }
    return res;
}

std::vector<int> sort_merge(std::vector<int>& arr) {
    if (arr.size() <= 1) return arr;
    size_t mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());
    return merge(sort_merge(left), sort_merge(right));
}

int main() {
    std::vector<int> v(9);
    std::cin >> v;
    std::cout << sort_merge(v) << '\n' << count;
    return 0;
}