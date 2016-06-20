#include <bits/stdc++.h>

using namespace std;
#define INF 100000000
#define MAX_TAG_SIZE 20
const double PHONE_COST = 1.00;
const double EMAIL_COST = 0.80;
const double OVERBOND_COST = 0.50;

/*
read the node information
*/
void read_nodes(string name, unordered_map<int,string>& num_to_name, vector<int>& pos_to_num, vector<int>& num_to_pos, int& size)
{
    ifstream f (name.c_str());
    string buffer;
    int cnt = 0;
    while (!getline(f, buffer).eof()) {
        int num;
        char c_tag[MAX_TAG_SIZE];
        sscanf(buffer.c_str(), "%d %100s", &num, c_tag);
        string tag = c_tag;
        num_to_name[num] = c_tag;
        pos_to_num.push_back(num);
        cnt++;
    }
    size = cnt + 1;
    num_to_pos.resize(size);
    for (int i = 0; i < pos_to_num.size(); i++)
        num_to_pos[pos_to_num[i]] = i;
    f.close();
}

void add_edge(vector<vector<bool> >& conn, vector<vector<double> >& cost, vector<int>& degree, int vi, int vj, string name)
{

        if (conn[vi][vj] == false) {
            degree[vi]++;
            degree[vj]++;
            conn[vi][vj] = true;
            conn[vj][vi] = true;
        }

        if (name == "Phone") {
            cost[vi][vj] += PHONE_COST;
            cost[vj][vi] += PHONE_COST;
        }
        else if (name == "Email") {
            cost[vi][vj] += EMAIL_COST;
            cost[vj][vi] += EMAIL_COST;
        }
        else if (name == "Overbond") {
            cost[vi][vj] += OVERBOND_COST;
            cost[vj][vi] += OVERBOND_COST;
        }
}

void read_edges(string name, vector<vector<bool> >& conn, vector<vector<double> >& cost, vector<int>& degree)
{
    ifstream f (name.c_str());
    string buffer;
    while (!getline(f, buffer).eof()) {
        if (buffer[0] != 'e') continue;
        int vi, vj;
        char c_tag[MAX_TAG_SIZE];
        string s;
        sscanf(buffer.c_str(), "%*c %d %d %100s", &vi, &vj, c_tag);
        s = c_tag;
        add_edge(conn, cost, degree, vi, vj, s);
    }
    f.close();
}

void init_graph(vector<vector<bool> >& conn, vector<vector<double> >& cost, vector<int>& degree, int size)
{
    conn.resize(size);
    cost.resize(size);
    degree.resize(size, 0);
    for (int i = 0; i < size; i++)
    {
       conn[i].resize(size, false);
       cost[i].resize(size, 0);
    }

}
void ordering_nodes(vector<vector<bool> >& conn, int size, vector<int>& pos_to_num, vector<int>& num_to_pos, vector<int>& degree, vector<int>& order_list)
{
    size = pos_to_num.size();
    bool check[size];
    memset(check,false,sizeof(check));
    int cnt = pos_to_num.size();
    while (cnt--)
    {
        int mi = INF, idx;
        for (int i = 0; i < size; i++)
        {
            if (check[i]) continue;
            if (degree[pos_to_num[i]] < mi) {
                mi = degree[pos_to_num[i]];
                idx = i;
            }
        }

        for (int i = 0; i < conn[pos_to_num[idx]].size(); i++)
        {
            if (conn[pos_to_num[idx]][i])
                degree[i]--;
        }
        order_list.push_back(pos_to_num[idx]);
        check[idx] = true;
    }
}

void clique_helper(deque<int> node_list, vector<vector<bool> >& conn, int size, int &max_ans, vector<int> cur_list, vector<int>& ans_list)
{
    if (node_list.size() == 0) {
        if (size > max_ans) {
            max_ans = size;
            ans_list.clear();
            for (int i = 0; i < cur_list.size(); i++)
             {
                ans_list.push_back(cur_list[i]);
             }
        }
        return;
    }
    while (node_list.size()) {
        if (size + node_list.size() <= max_ans) return;
        int vi = node_list.front();
        cur_list.push_back(vi);
        node_list.pop_front();
        deque<int> new_list;
        for (deque<int>::iterator it = node_list.begin(); it != node_list.end(); it++)
            if (conn[vi][*it]) new_list.push_back(*it);
        clique_helper(new_list, conn, size+1, max_ans, cur_list, ans_list);
        cur_list.pop_back();
    }
}

void clique(vector<int>& order_list, vector<vector<bool> >& conn, vector<int>& ans_list)
{
    int max_ans = 0;
    deque<int> node_list;
    vector<int> cur_list;
    for (int i = 0; i < order_list.size(); i++)
        node_list.push_back(order_list[i]);
    clique_helper(node_list, conn, 0, max_ans, cur_list, ans_list);
}

double cal_total_cost(vector<int>& ans_list, vector<vector<double> >& cost)
{
    double cost_sum = 0;
    for (int i = 0; i < ans_list.size(); i++)
        for (int j = i + 1; j < ans_list.size(); j++)
            cost_sum += cost[ans_list[i]][ans_list[j]];
    return cost_sum;
}

int main(int argc, char *argv[])
{
    assert(argc == 3);
    int size;
    vector<vector<bool> > conn;
    vector<int> degree;
    vector<vector<double> > cost;
    vector<int> order_list;
    unordered_map <int, string> num_to_name;
    vector<int> pos_to_num;
    vector<int> num_to_pos;

    read_nodes(argv[1], num_to_name, pos_to_num, num_to_pos, size);
    init_graph(conn, cost, degree, size);
    read_edges(argv[2], conn, cost, degree);
    ordering_nodes(conn, size, pos_to_num, num_to_pos, degree, order_list);
    vector<int> ans_list;

    clique(order_list, conn, ans_list);
    sort(ans_list.begin(), ans_list.end());
    ofstream outfile;
    outfile.open("result.txt");
    for (int i = 0; i < ans_list.size(); i++)
        outfile << ans_list[i] << " " << num_to_name[ans_list[i]] << endl;
    //cout << cal_total_cost(ans_list, cost) << endl;
    outfile.close();

    return 0;
}
