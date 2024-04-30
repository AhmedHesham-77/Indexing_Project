#include <bits/stdc++.h>

using namespace std;

/*
5
1
1
2
2 3
3
4 5 6
4
7 8 9 10
5
11 12 13 14 15
 */

void write_file() {
    int n;
    cin >> n;
    vector<vector<int>> file_data(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        vector<int> elements(m);
        for (auto &j: elements)
            cin >> j;
        file_data[i] = elements;
    }

    fstream data_file{"D:\\University\\File Structure\\2024\\SL\\Indexing\\data.dat",
                      ios::in | ios::out | ios::binary};
    fstream index_file{"D:\\University\\File Structure\\2024\\SL\\Indexing\\index.dat",
                       ios::in | ios::out | ios::binary};

    int offset = 0, deleted = 0;
    for (int i = 0; i < n; ++i) {
        int sz = file_data[i].size();
        index_file.write(reinterpret_cast<const char *>(&offset), sizeof(int));
        index_file.write(reinterpret_cast<const char *>(&sz), sizeof(int));
        index_file.write(reinterpret_cast<const char *>(&deleted), sizeof(int));

        for (auto j: file_data[i])
            data_file.write(reinterpret_cast<const char *>(&j), sizeof(int));

        offset += sz;
    }

    data_file.close(), index_file.close();
}

void read_data() {
    fstream data_file{"D:\\University\\File Structure\\2024\\SL\\Indexing\\data.dat",
                      ios::in | ios::out | ios::binary};
    fstream index_file{"D:\\University\\File Structure\\2024\\SL\\Indexing\\index.dat",
                       ios::in | ios::out | ios::binary};

    int offset, sz, deleted;
    while (!index_file.eof()) {
        index_file.read(reinterpret_cast<char *>(&offset), sizeof(int));
        index_file.read(reinterpret_cast<char *>(&sz), sizeof(int));
        index_file.read(reinterpret_cast<char *>(&deleted), sizeof(int));

        if (!deleted) {
            data_file.seekg(offset * sizeof(int));
            for (int i = 0; i < sz; ++i) {
                int val;
                data_file.read(reinterpret_cast<char *>(&val), sizeof(int));
                cout << val << ' ';
            }
            cout << '\n';
        }
    }

    index_file.close(), data_file.close();
}

int main() {
//    write_file();
//    read_data();
}