
        void save_stock() {
            std::ofstream fout("stock.csv");
            fout << a_stock << "," << b_stock <<