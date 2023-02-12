class Solution {
public:
    vector<int> ranks;
    vector<set<int>> edges;
    vector<vector<int>> sol;
    int dfs(int i) {
      //  cout<< "visiting " << i << "rank " << ranks[i] << "\n";
        int minRank = ranks[i];
        auto it = edges[i].begin();
        while (it != edges[i].end()) {
            int nbr = *it;
            if (nbr == -1) { continue; }
            bool gt = true;
            if (ranks[nbr] <= ranks[i] + 1) {
                gt = false;
               // cout<< "keeping " << nbr << "at " << ranks[nbr] << "\n";
            } else if (ranks[nbr] != INT_MAX ){
                it++;
                continue;
            } else {
              //  cout<< "setting " << nbr << "to " << ranks[i] + 1 << "\n";
            }
            
            ranks[nbr] = min(ranks[nbr], ranks[i] + 1);
            minRank = min(minRank, ranks[nbr]);
          //  cout<< "ive seen " << minRank <<"\n";
            if (gt) {
                
             //   auto old = edges[nbr].find(i);
               // replace (edges[nbr].begin(), edges[nbr].end(), nbr, -1); 
                
               edges[nbr].erase(i);
              //  edges[nbr].insert(old, -1);
             //   cout << "dfs " << nbr << "\n";
                int nbrMinRank = dfs(nbr);
                // cout<< i << " received " << nbrMinRank <<"\n";
                if (nbrMinRank > ranks[i]) {
                   // cout << "pushing back " << "\n";
                    vector<int> v = {i, nbr};
                    sol.push_back(v);
                }
                minRank = min(nbrMinRank, minRank);
               // cout << "minRank  " << minRank<< "\n";
            }
            it++;
        }
        return minRank;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        set<int> v;
        edges.resize(n, v);
        ranks.resize(n, INT_MAX);
        for (auto c : connections) {
            edges[c[0]].insert(c[1]);
            edges[c[1]].insert(c[0]);
        }
        ranks[0] = 0;
        dfs(0);
        return sol;
    }
};
