#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe() 
{  
}

PmergeMe::PmergeMe(const PmergeMe& rhs)
{
    _vector   = rhs._vector;
    _vecPairs = rhs._vecPairs;
    _deque    = rhs._deque;
    _deqPairs = rhs._deqPairs;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
    if (this != &rhs)
    {
        _vector   = rhs._vector;
        _vecPairs = rhs._vecPairs;
        _deque    = rhs._deque;
        _deqPairs = rhs._deqPairs;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

void    PmergeMe::addNumber(int n)
{
    this->_deque.push_back(n);
    this->_vector.push_back(n);
    return; 
}


void PmergeMe::extractBigs(const std::vector<Pair> &pairs,
                           std::vector<int> &bigs)
{
    bigs.clear();
    bigs.reserve(pairs.size());
    for (std::size_t i = 0; i < pairs.size(); ++i)
        bigs.push_back(pairs[i].big);
}

void PmergeMe::mapPairOrder(const std::vector<int> &bigs,
                            const std::vector<Pair> &pairs,
                            std::vector<std::size_t> &pairOrder)
{
    pairOrder.assign(bigs.size(), 0);
    std::vector<bool> used(pairs.size(), false);

    for (std::size_t k = 0; k < bigs.size(); ++k)
    {
        int v = bigs[k];
        for (std::size_t i = 0; i < pairs.size(); ++i)
        {
            if (!used[i] && pairs[i].big == v)
            {
                pairOrder[k] = i;
                used[i]      = true;
                break;
            }
        }
    }
}

void PmergeMe::buildMainChain(const std::vector<int> &bigs,
                              const std::vector<Pair> &pairs,
                              const std::vector<std::size_t> &pairOrder,
                              bool hasStraggler,
                              std::vector<int> &mainChain)
{
    mainChain.clear();
    mainChain.reserve(bigs.size() * 2 + (hasStraggler ? 1 : 0));

    for (std::size_t k = 0; k < bigs.size(); ++k)
        mainChain.push_back(bigs[k]);

    std::size_t firstPairIndex = pairOrder[0];
    int         firstSmall     = pairs[firstPairIndex].small;

    mainChain.insert(mainChain.begin(), firstSmall);
}

void PmergeMe::buildPendings(const std::vector<int> &bigs,
                             const std::vector<Pair> &pairs,
                             const std::vector<std::size_t> &pairOrder,
                             bool hasStraggler,
                             int straggler,
                             const std::vector<int> &mainChain,
                             std::vector<Pending> &pendings)
{
    pendings.clear();
    pendings.reserve(pairs.size() - 1 + (hasStraggler ? 1 : 0));

    for (std::size_t k = 1; k < bigs.size(); ++k)
    {
        std::size_t pairIdx = pairOrder[k];
        int         small   = pairs[pairIdx].small;

        Pending p;
        p.value  = small;
        p.maxPos = 1 + k;
        pendings.push_back(p);
    }

    if (hasStraggler)
    {
        Pending p;
        p.value  = straggler;
        p.maxPos = mainChain.size();
        pendings.push_back(p);
    }
}

void PmergeMe::buildInsertionOrder(const std::vector<Pending> &pendings,
                                   std::vector<std::size_t> &insertionOrder)
{
    insertionOrder.clear();

    std::size_t P = pendings.size();
    if (P == 0)
        return;

    std::vector<std::size_t> jacobs;
    jacobs.push_back(1);

    if (P > 1)
    {
        jacobs.push_back(3);
        while (true)
        {
            std::size_t sz   = jacobs.size();
            std::size_t next = jacobs[sz - 1] + 2 * jacobs[sz - 2];
            if (next > P)
                break;
            jacobs.push_back(next);
        }
    }

    insertionOrder.reserve(P);

    std::size_t prev = 0;

    for (std::size_t k = 0; k < jacobs.size(); ++k)
    {
        std::size_t cur = jacobs[k];
        if (cur > P)
            cur = P;
        if (cur <= prev)
            continue;

        for (std::size_t i = cur; i > prev; --i)
            insertionOrder.push_back(i - 1);

        prev = cur;
    }

    if (prev < P)
    {
        for (std::size_t i = P; i > prev; --i)
            insertionOrder.push_back(i - 1);
    }
}


void PmergeMe::insertPendings(std::vector<int> &mainChain,
                              const std::vector<Pending> &pendings,
                              const std::vector<std::size_t> &insertionOrder)
{
    for (std::size_t t = 0; t < insertionOrder.size(); ++t)
    {
        std::size_t idx   = insertionOrder[t];
        int         v     = pendings[idx].value;
        std::size_t limit = pendings[idx].maxPos;

        if (limit > mainChain.size())
            limit = mainChain.size();

        std::size_t left  = 0;
        std::size_t right = limit;

        while (left < right)
        {
            std::size_t mid = (left + right) / 2;
            if (v < mainChain[mid])
                right = mid;
            else
                left = mid + 1;
        }
        mainChain.insert(mainChain.begin() + left, v);
    }
}

/*------------VECTOR------------*/

std::vector<int>    PmergeMe::getVector()
{
    return _vector;
}
        
PairResult buildPairsVector(const std::vector<int> &src)
{
    PairResult result;
    result.hasStraggler = false;
    result.straggler    = 0;
    result.pairs.clear();

    std::size_t size = src.size();
    if (size == 0)
        return result;

    std::size_t end = size;
    if (size % 2 != 0)
    {
        result.hasStraggler = true;
        result.straggler    = src[size - 1];
        end                 = size - 1;
    }

    result.pairs.reserve(end / 2);
    for (std::size_t i = 0; i < end; i += 2)
    {
        int a = src[i];
        int b = src[i + 1];

        Pair p;
        p.small = std::min(a, b);
        p.big   = std::max(a, b);
        result.pairs.push_back(p);
    }
    return result;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &c)
{
    if (c.size() <= 1)
        return;

    PairResult           pr       = buildPairsVector(c);
    const std::vector<Pair> &pairs = pr.pairs;
    bool                 hasStraggler = pr.hasStraggler;
    int                  straggler    = pr.straggler;

    std::vector<int> bigs;
    extractBigs(pairs, bigs);
    fordJohnsonVector(bigs);

    std::vector<std::size_t> pairOrder;
    mapPairOrder(bigs, pairs, pairOrder);

    std::vector<int> mainChain;
    buildMainChain(bigs, pairs, pairOrder, hasStraggler, mainChain);

    std::vector<Pending> pendings;
    buildPendings(bigs, pairs, pairOrder, hasStraggler, straggler,
                  mainChain, pendings);

    std::vector<std::size_t> insertionOrder;
    buildInsertionOrder(pendings, insertionOrder);

    insertPendings(mainChain, pendings, insertionOrder);

    c = mainChain;
}

void PmergeMe::sortVector()
{
    fordJohnsonVector(_vector);
}






/*------------DEQUE------------*/

std::deque<int>     PmergeMe::getDeque()
{
    return _deque;
}
PairResult buildPairsDeque(const std::deque<int> &src)
{
    PairResult result;
    result.hasStraggler = false;
    result.straggler    = 0;
    result.pairs.clear();

    std::size_t size = src.size();
    if (size == 0)
        return result;

    std::size_t end = size;
    if (size % 2 != 0)
    {
        result.hasStraggler = true;
        result.straggler    = src[size - 1];
        end                 = size - 1;
    }

    result.pairs.reserve(end / 2);
    for (std::size_t i = 0; i < end; i += 2)
    {
        int a = src[i];
        int b = src[i + 1];

        Pair p;
        p.small = std::min(a, b);
        p.big   = std::max(a, b);
        result.pairs.push_back(p);
    }
    return result;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &c)
{
    if (c.size() <= 1)
        return;

    PairResult           pr       = buildPairsDeque(c);
    const std::vector<Pair> &pairs = pr.pairs;
    bool                 hasStraggler = pr.hasStraggler;
    int                  straggler    = pr.straggler;

    std::vector<int> bigs;
    extractBigs(pairs, bigs);
    fordJohnsonVector(bigs);

    std::vector<std::size_t> pairOrder;
    mapPairOrder(bigs, pairs, pairOrder);

    std::vector<int> mainChain;
    buildMainChain(bigs, pairs, pairOrder, hasStraggler, mainChain);

    std::vector<Pending> pendings;
    buildPendings(bigs, pairs, pairOrder, hasStraggler, straggler,
                  mainChain, pendings);

    std::vector<std::size_t> insertionOrder;
    buildInsertionOrder(pendings, insertionOrder);

    insertPendings(mainChain, pendings, insertionOrder);

    c.assign(mainChain.begin(), mainChain.end());
}


void PmergeMe::sortDeque()
{
    fordJohnsonDeque(_deque);
}



std::ostream&  operator<<(std::ostream& os, std::vector<int> const& v) 
{
    for (size_t i = 0; i < v.size(); ++i)
        os << v[i] << " ";
    return os;

}

std::ostream& operator<<(std::ostream& os, std::deque<int> const& d) 
{
    for (size_t i = 0; i < d.size(); ++i)
        os << d[i] << " ";
    return os;
}