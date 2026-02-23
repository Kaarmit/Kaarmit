#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <algorithm>
#include <cctype>
#include <ostream>



struct Pair {
    int         small;
    int         big;
};

struct PairResult {
    std::vector<Pair> pairs;
    bool              hasStraggler;
    int               straggler;
};

struct Pending {
    int         value;   
    std::size_t maxPos;
};

class PmergeMe
{
    public:
    
        PmergeMe();
        PmergeMe(const PmergeMe& rhs);
        PmergeMe& operator=(const PmergeMe& rhs);
        ~PmergeMe();
    
        void                addNumber(int n);
        void                sortVector();
        void                sortDeque();
        std::vector<int>    getVector();
        std::deque<int>     getDeque();
        

    
    private:

        
        /*-----VECTOR-----*/
        
        std::vector<int>    _vector;
        std::vector<Pair>   _vecPairs;
        
 
        /*-----DEQUE-----*/
        std::deque<int> _deque;
        std::deque<Pair> _deqPairs;
        

        
    static void        extractBigs(const std::vector<Pair> &pairs,
                    std::vector<int> &bigs);

    static void        mapPairOrder(const std::vector<int> &bigs,
                    const std::vector<Pair> &pairs,
                    std::vector<std::size_t> &pairOrder);

    static void        buildMainChain(const std::vector<int> &bigs,
                    const std::vector<Pair> &pairs,
                    const std::vector<std::size_t> &pairOrder,
                    bool hasStraggler,
                    std::vector<int> &mainChain);
    static void        buildPendings(const std::vector<int> &bigs,
                    const std::vector<Pair> &pairs,
                    const std::vector<std::size_t> &pairOrder,
                    bool hasStraggler,
                    int straggler,
                    const std::vector<int> &mainChain,
                    std::vector<Pending> &pendings);                     
    static void        buildInsertionOrder(const std::vector<Pending> &pendings,
                    std::vector<std::size_t> &insertionOrder);
    static void        insertPendings(std::vector<int> &mainChain,
                    const std::vector<Pending> &pendings,
                    const std::vector<std::size_t> &insertionOrder);
                              
    static void fordJohnsonVector(std::vector<int> &c);
    static void fordJohnsonDeque(std::deque<int> &c);
        
};

PairResult   buildPairsVector(const std::vector<int> &src);
PairResult   buildPairsDeque(const std::deque<int> &src);

std::ostream&          operator<<(std::ostream& os, std::vector<int> const& v);
std::ostream&          operator<<(std::ostream& os, std::deque<int> const& v);




#endif