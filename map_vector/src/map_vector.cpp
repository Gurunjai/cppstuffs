#include <iostream>
#include <unordered_map>
#include <map>
#include <chrono>
#include <deque>
#include <sstream>

#define ROW_CNT 6
#define COL_CNT 3
#define MAX_SIZE (ROW_CNT * COL_CNT)
#define MAX_MAP_SIZE 10

/* 1D Representation of 2D Array  6 rows and 3 columns*/
using MapBins = std::map<std::pair<int, int>, long>;
using MapRuleArrMap = std::unordered_map<std::string, MapBins>;
using MapRuleQueue = std::pair<std::chrono::milliseconds, std::string>;

class MapRuleLRU
{
public:
    int m;
    std::deque<MapRuleQueue> dq;
    MapRuleArrMap mrMap;

    MapRuleLRU(int capacity)
    {
        this->m = capacity;
    }

    MapBins& get(std::string maprule, int &rc)
    {
        MapBins out;
        if (!mrMap.count(maprule)) {
            rc = -1;
            return out;
        }

        for (std::deque<MapRuleQueue>::iterator it = dq.begin(); it != dq.end();)
        {
            if (it->second == maprule) {
                it = dq.erase(it);
            } else {
                ++it;
            }
        }

        using namespace std::chrono;
        auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        dq.push_front(std::make_pair(ms, maprule));

        rc = 0;
        return mrMap.at(maprule);
    }

    void put(std::string maprule, int rIdx, int cIdx, long value)
    {
        if (rIdx >= ROW_CNT || cIdx >= COL_CNT) {
            return;
        }

        int s = dq.size();

        if (!mrMap.count(maprule)) {
            if (s == m) {
                auto era = dq.back();
                mrMap.erase(era.second);
                dq.pop_back();
            }
            // Add to the map
            MapBins mval;
            initMapBins(mval);
            mrMap[maprule] = mval;
        } else {
            for (auto it = dq.begin(); it != dq.end(); )
            {
                if (it->second == maprule) {
                    it = dq.erase(it);
                } else {
                    ++it;
                }
            }
        }
        auto &inMap = mrMap[maprule];
        inMap.insert_or_assign(std::make_pair(rIdx, cIdx), value);
        using namespace std::chrono;
        auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        dq.push_front(std::make_pair(ms, maprule));
    }

    void dump(std::string maprule)
    {
        int rc = 0;
        auto val = get(maprule, rc);
        if (rc == -1) {
            std::cerr << "Maprule: " << maprule.c_str() << " not found in LRU" << std::endl;
            return;
        }
        
        std::cout << "Maprule: " << maprule.c_str() << std::endl;
        print(val);
    }

    void dumpAll()
    {
        for (const auto & [k, v] : mrMap) {
            std::cout << "Maprule: " << k.c_str() << std::endl;
            print(v);
        }
    }

private:
    void print(const MapBins& val)
    {
        for (const auto & [k,v] : val) {
            if (v != 0)
                std::cout << "[ " << k.first << ", " << k.second << "]: " << v << std::endl;
        }
    }

    void initMapBins(MapBins &out)
    {
        for (int ii = 0; ii < ROW_CNT; ii++)
            for (int jj = 0; jj < COL_CNT; jj++)
                out.emplace(std::make_pair(ii, jj), 0);
    }
};

int main (void)
{
    MapRuleLRU mr(MAX_MAP_SIZE);

    mr.put("r1", 3, 2, 50000);
    mr.dump("r1");
    mr.put("engr", 1, 2, 10000);
    mr.put("r1", 3, 0, 2000);
    mr.put("engr", 3, 4, 20000);
    mr.put("engr", 6, 2, 30000);
    mr.dump("engr");
    mr.dump("r1");
    mr.dump("r2");

    std::cout << std::endl << std::endl;
    for (int i = 0; i < 40000; i++) {
        std::stringstream buf;
        buf << "engr_mr_i_";
        buf << i + 1;

        mr.put(buf.str(), i % ROW_CNT, i % COL_CNT, i * 1000);
    }
    mr.dumpAll();

    return 0;
}