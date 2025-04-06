#include <vector>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <cfloat>

template<typename data_type>
class Algorithm {
protected:
    std::vector<data_type> array;
    std::vector<std::chrono::duration<double, std::milli>> runtimes;

public:
    void setArray(const std::vector<data_type> &a){
        this->array = a;
    }

    std::vector<data_type> getArray() {
        return this->array;
    }

    void addLastRuntime(const auto &current_runtime) {
        this->runtimes.push_back(current_runtime);
    }

    const auto& getSortTimes() {
        return runtimes;
    }

     friend std::ostream& operator<<(std::ostream &out, const Algorithm<data_type>& obj) {
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

template<typename data_type>
class Mergesort : public Algorithm<data_type> {
    void merge(const int left, const int middle, const int right)
    {
        const int s1(middle - left + 1), s2(right - middle);
        int i, j, k;
        std::vector<data_type> L(s1 + 1), R(s2 + 1);
        for (i = 0; i < s1; ++i)
            L[i] = this->array[left + i];

        for (i = 0; i < s2; ++i)
            R[i] = this->array[middle + i + 1];

        i = 0; j = 0; k = left;
        while (i < s1 && j < s2)
            if (L[i] <= R[j])
                this->array[k++] = L[i++];
            else
                this->array[k++] = R[j++];

        while (i < s1)
            this->array[k++] = L[i++];

        while (j < s2)
           this->array[k++] = R[j++];
    }

public:
    explicit Mergesort() = default;

    void sort(const int left, const int right, const int order = 0) {
        if (left >= right)
            return;

        const int middle = left + (right - left) / 2;
        sort(left, middle, order);
        sort(middle + 1, right, order);
        merge(left, middle, right);
    }

    ~Mergesort() = default;
};

template<typename data_type>
class Shellsort : public Algorithm<data_type>{
public:
    explicit Shellsort() = default;

    void sort(const int left, const int n, const int order = 0) {

        // Tokuda's sequence
        double gap = 1;
        while (2.25 * gap < n) {
            gap *= 2.25;
        }

        while (gap >= 1) {
            const int gap_int = static_cast<int>(gap);

            for (int i = gap_int; i < n; ++i) {
                const int tmp = this->array[i];
                int j = i;

                while (j >= gap_int && this->array[j - gap_int] > tmp) {
                    this->array[j] = this->array[j - gap_int];
                    j -= gap_int;
                }

                this->array[j] = tmp;
            }

            gap /= 2.25;
        }
    }

    ~Shellsort() = default;
};

template<typename data_type>
class Radixsort : public Algorithm<data_type> {
private:
    const int base = 10;

    data_type maxim(const auto& v, const int n) {
        data_type max = v[0];
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
    void sort(const int left, const int n, const int order = 0) {
        const data_type max = maxim(this->array, n);
        for (int exp = 1; max / exp > 0; exp *= base) {
            std::vector<int> freq(base, 0), out(n);

            for (int i = 0; i < n; ++i) {
                ++freq[(this->array[i] / exp) % base];
            }

            for (int i = 1; i < base; ++i) {
                freq[i] += freq[i - 1];
            }

            for (int i = n - 1; i >= 0; --i) {
                out[freq[(this->array[i] / exp) % base] - 1] = this->array[i];
                --freq[(this->array[i] / exp) % base];
            }

            for (int i = 0; i < n; ++i) {
                this->array[i] = out[i];
            }
        }
    }

    ~Radixsort() = default;
};

template<typename data_type>
class Heapsort : public Algorithm<data_type> {
private:
    void heapify(std::vector<data_type>& array, const int n, const int i){
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
    void sort(const int left, const int n, const int order = 0) {
        // Max heap
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(this->array, n, i);
        }

        for (int i = n - 1; i >= 0; --i) {
            std::swap(this->array[0], this->array[i]);
            heapify(this->array, i, 0);
        }
    }
};

template<typename data_type>
class Timsort : public Algorithm<data_type> {
private:
    void merge(std::vector<data_type>& array, const int left, const int middle, const int right)
    {
        const int s1(middle - left + 1), s2(right - middle);
        int i, j, k;
        std::vector<data_type> L(s1 + 1), R(s2 + 1);
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

    void insertion(std::vector<data_type>& array, const int left, const int right) {
        int i(left + 1);
        while (i <= right) {
            int j(i - 1);
            while (j >= left && array[j] > array[i]) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = array[i];
            i++;
        }
    }

public:
    void sort(const int start, const int n, const int order = 0) {
        int run(32), left(start), right(n), i(start);
        int size(run);

        while (i < n) {
            insertion(this->array, i, std::min(i + run - 1, n - 1));
            i += run;
        }

        while (size < n) {
            while (left < n) {
                const int mid = left + size - 1;
                right = std::min(left + 2 * size - 1, n - 1);
                if (mid < right) {
                    merge(this->array, left, mid, right);
                }
                left += 2 * size;
            }
            left = 0;
            size *= 2;
        }
    }
};

template<typename data_type>
class AVL : public Algorithm<data_type> {
    class node {
    public:
        data_type value;
        int height;
        node *left;
        node *right;
    };
private:

    node *createNode(data_type _value) {
        node *Node = new node();
        Node->value = _value;
        Node->left = nullptr;
        Node->right = nullptr;
        Node->height = 1;

        return (Node);
    }

    int getHeight(const node *Node) {
        if (Node == nullptr) {
            return 0;
        }
        return Node->height;
    }

    int getBalance(const node *Node) {
        if (Node == nullptr) {
            return 0;
        }

        return getHeight(Node->right) - getHeight(Node->left);
    }

    node *rotRight(node *Node) {
        //std::cout << "rotRight on " << Node->value << std::endl;
        node *parent = Node->left;
        node *temp = parent->right;
        parent->right = Node;
        Node->left = temp;
        Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;
        parent->height = std::max(getHeight(parent->left), getHeight(parent->right)) + 1;
        return parent;
    }

    node *rotLeft(node *Node) {
        //std::cout << "rotLeft on " << Node->value << std::endl;
        node *parent = Node->right;
        node *temp = parent->left;
        parent->left = Node;
        Node->right = temp;
        Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;
        parent->height = std::max(getHeight(parent->left), getHeight(parent->right)) + 1;
        return parent;
    }

    node *insert(node *root, int _value) {
        //std::cout << "insert " << _value << std::endl;
        if (root == nullptr) {
            return createNode(_value);
        }

        // Inseram frumos noua valoare

        if (_value < root->value) {
            root->left = insert(root->left, _value);
        } else {
            root->right = insert(root->right, _value);
        }

        //std::cout << "cnt for " << root->value << std::endl;

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        int balanceMe = getBalance(root);
        int balanceLeft = getBalance(root->left);
        int balanceRight = getBalance(root->right);
        //std::cout << "balance(" << root->value << ") " << balanceMe << " l:" << balanceLeft << " r:" << balanceRight << std::endl;
        //LL
        if (balanceMe <= -2 && balanceLeft < 0) {
            //std::cout << "LL on " << root->value << " " << balanceMe <<  " " << balanceRight << std::endl;
            return rotRight(root);
        }

        //LR
        if (balanceMe <= -2 && balanceLeft > 0) {
            //std::cout << "LR on " << root->value << " " << balanceMe <<  " " << balanceRight << std::endl;
            root->left = rotLeft(root->left); // observati cum rotim frumos la dreapta aripa stanga
            return rotRight(root);  // apoi elegant totu la stanga
        }

        //RL
        if (balanceMe >= 2 && balanceRight <= 0) {
            //std::cout << "RL on " << root->value << " " << balanceMe <<  " " << balanceRight << std::endl;
            root->right = rotRight(root->right);
            return rotLeft(root);
        }

        //RR
        if (balanceMe >= 2 && balanceRight >= 0) {
            //std::cout << "RR on " << root->value << " " << balanceMe <<  " " << balanceRight << std::endl;
            return rotLeft(root);
        }

        return root;
    }

    void sortTree(node *root, std::vector<data_type> &finArray) {
        if (root == nullptr) {
            return;
        }
        sortTree(root->left, finArray);
        finArray.push_back(root->value);
        sortTree(root->right, finArray);
    }

public:
    void sort(const int left, const int n, const int order = 0) {
        node *Node = nullptr;
        for (int i = 0; i < n; ++i) {
            Node = insert(Node, this->array[i]);
        }

        this->array.clear();

        sortTree(Node, this->array);
    }
};

template<typename data_type>
class Default : public Algorithm<data_type> {
public:
    void sort(const int left, const int n, const int order = 0) {
        std::sort(this->array.begin(), this->array.end());
    }
};

template<typename Sortname, typename data_type>
class Test {
    std::string sort_name;
    std::string type;
    std::vector<data_type> template_array = {0, 1};
    std::string tests_path, results_path;

    void setStats(const std::string& path, const std::string& sort_name, const auto& sort_times) {
        const std::string file_name = path + "stats.csv";
        std::ofstream f(file_name, std::ios::app);
        if (!f.is_open()) {
            throw std::runtime_error("File does not exist: " + file_name);
        }

        f << sort_name << ',';
        for (auto const& time : sort_times) {
            f << time.count() << ',';
        }
        f << std::endl;
    }

    void setResult(const std::string& path, const std::string& sort_name, const std::string& file_name, const std::string& sort_type, const auto& algorithm) {
        namespace fs = std::filesystem;
        std::string dir_path = path + sort_name + "/" + sort_type;

        if (!fs::exists(dir_path)) {
            fs::create_directories(dir_path);
        }

        size_t pos = file_name.find_last_of('/');
        std::string new_file_name = (pos != std::string::npos) ? file_name.substr(pos + 1) : file_name;
        std::string file_path = dir_path + "/" + new_file_name;
        std::cout << std::format("[{}] Writing results to: {}", sort_type, file_path) << std::endl;

        std::ofstream file(file_path);
        if (!file) {
            file.open(file_path, std::ios::out);
        }
        file << algorithm;

        file.close();
    }

    void setup(const std::string& file_name) {
        std::vector<data_type> temp_array;
        std::ifstream f(file_name);
        if (!f.is_open()) {
            throw std::runtime_error("File does not exist: " + file_name);
        }

        data_type input;
        while (f >> input) {
            temp_array.push_back(input);
        }

        setTemplateArray(temp_array);
        f.close();
    }

    bool checkResult(auto& algorithm, bool order) {
        const auto sorted_array = algorithm.getArray();

        if (!sorted_array.size()) {
            return false;
        }

        if (sorted_array.empty()) {
            return false;
        }

        if (order == 0) {
            return std::is_sorted(sorted_array.begin(), sorted_array.end());
        }
        return std::is_sorted(sorted_array.begin(), sorted_array.end(), std::greater<>());
    }

    void setTemplateArray(std::vector<data_type> &temp) {
        this->template_array = temp;
    }

    std::vector<data_type> getTemplateArray() {
        return this->template_array;
    }

    void setTestsPath(const std::string& path) {
        this->tests_path = path + this->type + "/";
    }

    void setResultsPath(const std::string& path) {
        this->results_path = path;
    }

    void setDataType(const std::string& type) {
        std::cout << type << std::endl;
        if (type == "i") {
            this->type = "INT";
        } else if (type == "f") {
            this->type = "FLOAT";
        } else if (type == "y") {
            this->type = "ULL";
        } else {
            this->type = "UNDEFINED";
        }
    }

    void setSortName(const auto& sort_name) {
        std::string temp = sort_name + 1;
        temp.erase(temp.length() - 3);
        this->sort_name = temp + "_" + this->type;
    }

    std::string getTestsPath() {
        return this->tests_path;
    }

    std::string getResultsPath() {
        return this->results_path;
    }

    std::string getSortName() {
        return this->sort_name;
    }

public:
    explicit Test() {
        setDataType(typeid(data_type).name());
        setSortName(typeid(Sortname).name());
        setTestsPath("Tests/");
        setResultsPath("Results/");
    }

    void run() {
        Sortname algorithm;

        std::string sort_name = getSortName();
        std::string current_tests_path = getTestsPath();
        std::string current_results_path = getResultsPath();

        for (const auto& entry : std::filesystem::directory_iterator(current_tests_path)) {
            if (entry.is_regular_file()) {
                std::string file_name = current_tests_path + entry.path().filename().string();
                std::cout << std::endl << "Reading data from: " << file_name << std::endl;

                Test::setup(file_name);
                std::vector<data_type> unsorted_array = Test::getTemplateArray();

                std::cout << "Initial array length: " << unsorted_array.size() << std::endl;

                for (int order = 0; order <= 0; ++order) { // order <= 1 for descending
                    algorithm.setArray(unsorted_array);

                    auto start = std::chrono::high_resolution_clock::now();
                    algorithm.sort(0, unsorted_array.size(), order);
                    auto end = std::chrono::high_resolution_clock::now();

                    const std::chrono::duration<double, std::milli> current_runtime = end - start;

                    std::cout << std::format("[{}] Sorting time using {}: ", order == 0 ? "ASC" : "DESC", sort_name) << current_runtime << ' ';

                    const std::string status = Test::checkResult(algorithm, order) ? "OK" : "FAIL";
                    std::cout << status << std::endl;
                    if (status == "OK") {
                        algorithm.addLastRuntime(current_runtime);
                    } else {
                        const std::chrono::duration<double, std::milli> no_value{0.0};
                        algorithm.addLastRuntime(no_value);
                    }

                    Test::setResult(current_results_path, sort_name, file_name, order == 0 ? "ASC" : "DESC", algorithm);
                }
            }
        }
        const auto sort_times = algorithm.getSortTimes();
        Test::setStats(current_results_path, sort_name, sort_times);
    }

    ~Test() = default;
};

int main() {
    // Mergesort
    Test<Mergesort<int>, int> mergesort_int; mergesort_int.run();
    Test<Mergesort<unsigned long long>, unsigned long long> mergesort_ull; mergesort_ull.run();
    Test<Mergesort<float>, float> mergesort_float; mergesort_float.run();

    // Shellsort
    Test<Shellsort<int>, int> shellsort_int; shellsort_int.run();
    Test<Shellsort<unsigned long long>, unsigned long long> shellsort_ull; shellsort_ull.run();
    Test<Shellsort<float>, float> shellsort_float; shellsort_float.run();

    // Radixsort
    Test<Radixsort<int>, int> radixsort_int; radixsort_int.run();
    Test<Radixsort<unsigned long long>, unsigned long long> radixsort_ull; radixsort_ull.run();
    // Not working on float // Test<Radixsort<float>, float> radixsort_float; radixsort_float.run();

    // Heapsort
    Test<Heapsort<int>, int> heapsort_int; heapsort_int.run();
    Test<Heapsort<unsigned long long>, unsigned long long> heapsort_ull; heapsort_ull.run();
    Test<Heapsort<float>, float> heapsort_float; heapsort_float.run();

    // Timsort
    Test<Timsort<int>, int> timsort_int; timsort_int.run();
    Test<Timsort<unsigned long long>, unsigned long long> timsort_ull; timsort_ull.run();
    Test<Timsort<float>, float> timsort_float; timsort_float.run();

    // AVL Sort
    Test<AVL<int>, int> AVL_int; AVL_int.run();
    Test<AVL<unsigned long long>, unsigned long long> AVL_ull; AVL_ull.run();
    Test<AVL<float>, float> AVL_float; AVL_float.run();

    // Default STL
    Test<Default<int>, int> default_int; default_int.run();
    Test<Default<unsigned long long>, unsigned long long> default_ull; default_ull.run();
    Test<Default<float>, float> default_float; default_float.run();

    return 0;
}