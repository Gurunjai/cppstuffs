#include "metalCfg.h" 

ABase::ABase() {
}

ABase::~ABase() {

}

using MyPair = pair<LMeta*, MMeta*>;
using MyMap = unordered_map<int, MyPair>;
using MyIterate = MyMap::iterator;
using MyVariant = variant<LMeta*, MMeta*>;
using NewType = pair<ABase::Type, MyVariant>;

template<typename T>
T* ABase::GetMtd() {
    T aObj;
    return dynamic_cast<decltype(aObj)*>(this);
}

void ABase::init() {
    m_aObj[LEGACY] = make_unique<LMeta>();
    m_aObj[METAL] = make_unique<MMeta>();
}

ABase::Type ABase::getIndex(bool isMetal) {
    return isMetal ? METAL : LEGACY;
}

decltype(auto) ABase::GetMetadata(bool isMetal) noexcept {
    MyPair out;
    out.first = nullptr;
    out.second = nullptr;
    if (isMetal) {
        out.second = dynamic_cast<MMeta*>(m_aObj[METAL].get());
    } else {
        out.first = dynamic_cast<LMeta*>(m_aObj[LEGACY].get());
    }
    return out;
}

decltype(auto) ABase::GetPairMtd(bool isMetal) noexcept {
    MyMap out;
    MyPair tmp;
    tmp.first = nullptr;
    tmp.second = nullptr;
    if (isMetal) {
        tmp.second = dynamic_cast<MMeta*>(m_aObj[METAL].get());
        out[1] = tmp;
    } else {
        tmp.first = dynamic_cast<LMeta*>(m_aObj[LEGACY].get());
        out[0] = tmp;
    }

    return out;
}

decltype(auto) ABase::GetPair(bool isMetal) noexcept {
    pair<int, void*> out;
    if (isMetal) {
        out.first = 0;
        out.second = m_aObj[METAL].get();
    } else {
        out.first = 1;
        out.second = m_aObj[LEGACY].get();
    }

    return out;
}

decltype(auto) ABase::GetMtdPair(bool isMetal) noexcept {
    NewType out;
    if (isMetal) {
        out.first = ABase::METAL;
        out.second = dynamic_cast<MMeta*>(m_aObj[METAL].get());
    } else {
        out.first = ABase::LEGACY;
        out.second = dynamic_cast<LMeta*>(m_aObj[LEGACY].get());
    }

    return out;
}

decltype(auto) ABase::GetPtr(ABase::Type t) noexcept {
    return m_aObj[t].get();
}

decltype(auto) ABase::GetLMeta() {
    return dynamic_cast<LMeta*>(m_aObj[LEGACY].get());
}

decltype(auto) ABase::GetMMeta() {
    return dynamic_cast<MMeta*>(m_aObj[METAL].get());
}

void LMeta::init() {
    memset(&m_cfgTags, 0, sizeof(ConfigMdt));
}

void MMeta::init() {
    memset(&m_cfgTags, 0, sizeof(StoreConfig));
}

void MMeta::Set() {
    m_cfgTags.flags.rollback_fix ^= 1;
}

template<class T>
decltype(auto) getMeta(T test) {
    if constexpr (is_same<T, LMeta*>::value)
        return dynamic_cast<LMeta*>(test);
    else if constexpr (is_same<T, MMeta*>::value)
        return dynamic_cast<MMeta*>(test);
    else
        return nullptr;
}

template<int I>
decltype(auto) getMetaVal(MyVariant obj) {
    // if constexpr (is_same_v<decay_t<decltype(obj)>, LMeta*>) {
    //     return obj;
    // }
    // else if constexpr(is_same_v<decay_t<decltype(obj)>, MMeta*>) {
    //     return obj;
    // }

    // return nullptr;
    if constexpr (I == 0) {
        return get<LMeta*>(obj);
    } else if constexpr (I == 1) {
        return get<MMeta*>(obj);
    }
}

int main(void) {
    ABase aObj;
    aObj.init();

    // Default Access
    {
        cout << "Default Access:" << endl;
        LMeta* a = aObj.GetLMeta();
        cout << "\ta: " << a << endl;
        cout << "\tLMeta Rollback Fix: " << a->config().flags.rollback_fix << endl;

        MMeta* b = aObj.GetMMeta();
        cout << "\tb: " << b << endl;
        b->Set();
        cout << "\tMMeta Rollback Fix(Set): " << b->config().flags.rollback_fix << endl;
        b->Set();
        cout << "\tMMeta Rollback Fix(Clear): " << b->config().flags.rollback_fix << endl;
    };

    // With Pair and Client scope with tie
    {
        cout << endl << "With Pair and Client Scope" << endl;
        LMeta* x;
        MMeta* y;
        tie(x,y) = aObj.GetMetadata();
        cout << "\tX = " << x << endl;
        cout << "\tY = " << y << endl;
        cout << "\tFor Metal" << endl;
        tie(x,y) = aObj.GetMetadata(true);
        cout << "\tX = " << x << endl;
        cout << "\tY = " << y << endl;
    };
    
    // With Pair and scope of std::get
    {
        cout << endl << "With Pair and Scope of std::get" << endl;
        LMeta* lm;
        MMeta* mm;
        int flag = 0;
        auto tmp = aObj.GetMetadata(flag);
        cout << "\tLMeta Out: " << get<decltype(lm)>(tmp) << endl;

        flag = 1;
        tmp = aObj.GetMetadata(flag);
        cout << "\tMMeta out: " << get<decltype(mm)>(tmp) << endl;
    };

    // With Map and direct access
    {
        cout << endl << "With Map and Direct Access" << endl;
        auto m = aObj.GetPairMtd(false);
        MyIterate it;
        cout << "\tFor LMeta:" << endl;
        for (it = m.begin(); it != m.end(); ++it) {
            cout << "\t\t" << it->first << " : " << it->second.first << "\t" << it->second.second << endl;
        }

        m = aObj.GetPairMtd(true);
        cout << "\tFor MMeta:" << endl;
        for (it = m.begin(); it != m.end(); ++it) {
            cout << "\t\t" << it->first << " : " << it->second.first << "\t" << it->second.second << endl;
        }

    };

    // With Constexpr on single method on map
    {
        cout << endl << "With Constexpr on single method on map" << endl;
        auto m = aObj.GetPairMtd(false);
        cout << "\tFor LMeta:" << endl;
        for (auto s : m) {
            cout << "\t\tKey:\t" << s.first << endl;
            cout << "\t\tPair First:\t" << getMeta(s.second.first) << endl;
            cout << "\t\tPair Second:\t" << getMeta(s.second.second) << endl;
            getMeta(s.second.first)->Set("WHAT IF???");
            cout << "\t\tTest on Config:\t" << getMeta(s.second.first)->config().sTest << endl; 
            cout << "\t\tFlag on Config:\t" << getMeta(s.second.first)->config().flags.rollback_fix << endl; 
        }

        m = aObj.GetPairMtd(true);
        cout << "\tFor MMeta:" << endl;
        for (auto s : m) {
            cout << "\t\tKey:\t" << s.first << endl;
            cout << "\t\tPair First:\t" << getMeta(s.second.first) << endl;
            cout << "\t\tPair Second:\t" << getMeta(s.second.second) << endl;
            getMeta(s.second.second)->Set();
            cout << "\t\tFlag on Config:\t" << getMeta(s.second.second)->config().flags.rollback_fix << endl;
            getMeta(s.second.second)->Set();
            cout << "\t\tFlag on Config(clear):\t" << getMeta(s.second.second)->config().flags.rollback_fix << endl;
        }

    };

    // With constexpr on single method on pair
    {
        cout << endl << "With Constexpr on single method on map" << endl;
        auto p = aObj.GetMetadata();
        cout << "\tFor LMeta:" << endl;
        cout << "\t\tPair First:\t" << getMeta(p.first) << endl;
        cout << "\t\tPair Second:\t" << getMeta(p.second) << endl;
        getMeta(p.first)->Set("What?, How?, Why?");
        cout << "\t\tTest on Config STest:\t" << getMeta(p.first)->config().sTest << endl;

        p = aObj.GetMetadata(true);
        cout << "\tFor MMeta:" << endl;
        cout << "\t\tPair First:\t" << getMeta(p.first) << endl;
        cout << "\t\tPair Second:\t" << getMeta(p.second) << endl;
        getMeta(p.second)->Set();
        cout << "\t\tTest on Config Flag:\t" << getMeta(p.second)->config().flags.rollback_fix << endl;
        getMeta(p.second)->Set();
        cout << "\t\tTest on Config Flag(clear):\t" << getMeta(p.second)->config().flags.rollback_fix << endl;
    };

    // With std::variant on a pair
    {
        cout << endl << "With std::variant on a pair second" << endl;
        auto fn = [](const auto &elem) {
            if constexpr (is_same_v<decay_t<decltype(elem)>, LMeta*>) {
                elem->Set("What is this????");
                cout << "\t\tTest on Config STest:\t" << elem->config().sTest << endl;
            }
            else if constexpr (is_same_v<decay_t<decltype(elem)>, MMeta*>) {
                elem->Set();
                cout << "\t\tTest on Config Flag(set):\t" << elem->config().flags.rollback_fix << endl;
                elem->Set();
                cout << "\t\tTest on Config Flag(clear):\t" << elem->config().flags.rollback_fix << endl;
            }
        };

        auto p = aObj.GetMtdPair();
        cout << "\tFor LMeta:" << endl;
        cout << "\t\tPair First:\t" << p.first << endl;
        visit([](auto &&elem){cout << "\t\tPair Second:\t" << elem << endl; }, p.second);
        visit(fn, p.second);

        p = aObj.GetMtdPair(true);
        cout << "\tFor MMeta:" << endl;
        cout << "\t\tPair First:\t" << p.first << endl;
        visit([](auto &&elem){cout << "\t\tPair Second:\t" << elem << endl;}, p.second);
        visit(fn, p.second);
    };

    {
        cout << endl;
    };

    cout << endl;
    return 0;
}