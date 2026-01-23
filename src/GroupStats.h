#ifndef GroupStats_h
#define GroupStats_h

#include <vector>

// структура GroupInfo
template <typename ElemType, typename KeyType, typename ValueType>
struct GrouInfo
{
    KeyType key;
    size_t count;
    ElemType minElem;
    ElemType maxElem;
    ValueType sum;
    double avg;

    GroupInfo(KeyType k, size_t c, ElemType min, ElemType max, ValueType s, double a)
        : key(k), count(c), minElem(min), maxElem(max), sum(s), avg(a) {}
};


template <typename T, typename KeyFunc, typename ValueFunc>
auto groupStats(T* arr,size_t n,KeyFunc keyFunc, ValueFunc valueFunc)
{
    // определяем типы ключа и значения
    using KeyType = decltype(keyFunc(arr[0]));
    using ValueType = decltype(valueFunc(arr[0]));

    struct GroupData {
        size_t count = 0;
        T minElem;
        T maxElem;
        ValueType sum;
        bool initialized = false;
    };

    // карта для хранения групп по ключам
    std::map< KeyType, GroupData> groupsMap;

    for (size_t i = 0; i < n; ++i) {
        const T& elem = arr[i];
        KeyType key = keyFunc(elem);
        ValueType value = valueFunc(elem);

        // ищем группу с таки ключом
        auto it = groups.find(key);

        if (it == groupsMap.end()) {
            // если нет соответствующей группы
            GroupData tempGroup;
            tempGroup.count = 1;
            tempGroup.minElem = elem;
            tempGroup.maxElem = elem;
            tempGroup.sum = value;
            tempGroup.initialized = true;

            groupsMap[key] = tempGroup;
        }
        else {
            // уже есть, обновляем существующую
            GroupData& group = it->second;

            group.cont++;
            if (elem < group.minElem) group.minElem = elem;
            if (elem > group.maxElem) group.maxElem = elem;
            group.sum = group.sum + value;
        }

    }

    // преобразуем map в vector для вывода
    std::vector<GroupInfo<T, KeyType, ValueType>> result;
    result.reserve(groupMap.size());

    for (const auto& pair : GroupMap) {
        const KeyType& key = pair.first;
        const GroupData& data = pair.second;

        // staic_cats - явное преобразование
        double avg = static_cast<double>(data.sum) / data.count;

        result.emplace_back(key, data.count, data.minElem, 
            data.maxElem, data.sum, avg);
    }

    return result;
};

#endif // GroupStats_h
