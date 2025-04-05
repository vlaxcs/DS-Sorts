#include <vector> // Mergesort, Test
#include <iostream> // Mergesort
#include <chrono> // Test
#include <filesystem> // Test
#include <fstream> // Test

class Algorithm {
protected:
    std::vector<int> array;
    std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:
    void setArray(const std::vector<int> &a){
        this->array = a;
    }

    std::vector<int> getArray() {
        return this->array;
    }

    void addLastRuntime(const auto &current_runtime) {
        this->runtimes.push_back(current_runtime);
    };

    friend std::ostream& operator<<(std::ostream &out, const auto &obj) {
        out << "[";
        for (size_t i = 0; i < obj.array.size(); ++i) {
            out << obj.array[i];
            if (i != obj.array.size() - 1)
                out << ", ";
        }
        out << "]";
        return out;
    }
};

class Mergesort : public Algorithm {
    void merge(int left, int middle, int right)
    {
        const int s1(middle - left + 1), s2(right - middle);
        int i, j, k;
        std::vector<int> L(s1 + 1), R(s2 + 1);
        for (i = 0; i < s1; ++i)
            L[i] = array[left + i];

        for (i = 0; i < s2; ++i)
            R[i] = array[middle + i + 1];

        i = 0; j = 0; k = left;
        while (i < s1 && j < s2)
            if (L[i] <= R[j])
                array[k++] = L[i++];
            else
                array[k++] = R[j++];

        while (i < s1)
            array[k++] = L[i++];

        while (j < s2)
            array[k++] = R[j++];
    }

public:
    explicit Mergesort() = default;

    void sort(const int left, const int right) {
        if (left >= right)
            return;

        const int middle = left + (right - left) / 2;
        sort(left, middle);
        sort(middle + 1, right);
        merge(left, middle, right);
    }

    ~Mergesort() = default;
};

class Shellsort : public Algorithm{
public:
    explicit Shellsort() = default;

    void sort(const int left, const int n) {

        // Tokuda's sequence
        double gap = 1;
        while (2.25 * gap < n) {
            gap *= 2.25;
        }

        while (gap >= 1) {
            const int gap_int = static_cast<int>(gap);

            for (int i = gap_int; i < n; ++i) {
                const int tmp = array[i];
                int j = i;

                while (j >= gap_int && array[j - gap_int] > tmp) {
                    array[j] = array[j - gap_int];
                    j -= gap_int;
                }

                array[j] = tmp;
            }

            gap /= 2.25;
        }
    }

    ~Shellsort() = default;
};

class Radixsort : public Algorithm {
private:
    const int baza = 10;

    int maxim(std::vector<int> v, const int n) {
        int max = v[0];
        for (int i = 1; i < n; ++i) {
            if (v[i] > max) {
                max = v[i];
            }
        }
        return max;
    }

public:
    explicit Radixsort() = default;

    // LSD radix sort
    void sort(const int left, const int n) {
        const int max = maxim(array, n);
        for (int exp = 1; max / exp > 0; exp *= baza) {
            std::vector<int> freq(baza, 0), out(n);

            for (int i = 0; i < n; ++i) {
                freq[(array[i] / exp) % baza]++;
            }

            for (int i = 1; i < baza; ++i) {
                freq[i] += freq[i - 1];
            }

            for (int i = n - 1; i >= 0; --i) {
                out[freq[(array[i] / exp) % baza] - 1] = array[i];
                freq[(array[i] / exp) % baza]--;
            }

            for (int i = 0; i < n; ++i) {
                array[i] = out[i];
            }
        }
    }

    ~Radixsort() = default;
};

class Heapsort : public Algorithm {
private:
    void heapify(auto& array, const int n, const int i){
        int lg = i;
        int left = 2 * i + 1;
        int right = left + 1;

        // order matters
        if (left < n && array[left] > array[lg]) {
            lg = left;
        }

        if (right < n && array[right] > array[lg]) {
            lg = right;
        }

        if (lg != i) {
            std::swap(array[i], array[lg]);
            heapify(array, n, lg);
        }
    };

public:
    void sort(const int left, const int n) {
        // Max heap
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(array, n, i);
        }

        for (int i = n - 1; i >= 0; --i) {
            std::swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }
};

template<typename Sortname>
class Test {
    std::vector<int> template_array = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::string tests_path;

    void setup(const std::string& filename) {
        std::vector<int> temp_array;
        std::ifstream f(filename);
        if (!f.is_open()) {
            throw std::runtime_error("File does not exist: " + filename);
        }

        int input;
        while (f >> input) {
            temp_array.push_back(input);
        }

        setTemplateArray(temp_array);
        f.close();
    }

    void setTemplateArray(std::vector<int> &temp) {
        this->template_array = temp;
    }

    std::vector<int> getTemplateArray() {
        return this->template_array;
    }

    void setTestsPath() {
        this->tests_path = "Tests/";
    }

    std::string getTestsPath() {
        return this->tests_path;
    }

public:
    explicit Test() {
        setTestsPath();
    }

    void run() {
        Sortname algorithm;

        std::string current_path = getTestsPath();
        for (const auto& entry : std::filesystem::directory_iterator(current_path)) {
            if (entry.is_regular_file()) {
                std::string file_name = current_path + entry.path().filename().string();
                std::cout << std::endl << "Reading data from: " << file_name << std::endl;

                Test::setup(file_name);
                std::vector<int> unsorted_array = Test::getTemplateArray();
                algorithm.setArray(unsorted_array);

                std::cout << "Initial array length: " << unsorted_array.size() << std::endl;
                // std::cout << "Initial array: " << algorithm << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                algorithm.sort(0, unsorted_array.size() - 1); // configure lambda function
                auto end = std::chrono::high_resolution_clock::now();

                const std::chrono::duration<double, std::milli> current_runtime = end - start;

                //std::cout << "Sorted array: " << algorithm << std::endl;

                std::cout << std::format("Sorting time using {}: ", typeid(Sortname).name() + 1) << current_runtime;
                algorithm.addLastRuntime(current_runtime);
                std::cout << std::endl;
            }
        }
    }

    ~Test() = default;
};

#include <float.h>
int main() {
    Test<Mergesort> mergesort;
    Test<Shellsort> shellsort;
    Test<Radixsort> radixsort;
    Test<Heapsort> heapsort;
    mergesort.run();
    shellsort.run();
    radixsort.run();
    heapsort.run();
    return 0;
}