/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/sort-colors/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <cassert>
#include <chrono>
#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iterator>
#include <vector>
#include <span>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

class Solution {
public:
    /*!
        leetcode 75. Sort Colors:

            Given an array nums with n objects colored red, white, or blue, 
            sort them IN-PLACE so that objects of the same color are adjacent, 
            with the colors in the order red, white, and blue.

            We will use the integers 0, 1, and 2 to represent the color red, 
            white, and blue, respectively.

            You must solve this problem without using the library's sort function.

            n == nums.length
            1 <= n <= 300
            nums[i] is either 0, 1, or 2.

        Since the range of each input value is known, bucket sort can be used 
        even though the input must be sorted in-place.  This is becuase the 
        amount of storage used by bucket sort will remain constant regardless
        of the size of the input.

        Time = O(n)
        Space = O(1)
    */
    void sortColors_bucketSort(vector<int>& nums) {
        constexpr auto const range = 3;
        int bucket[range] = { 0 };
        for (auto const num : nums) {
            assert(0 <= num && 3 > num);
            ++bucket[num];
        }
        decay_t<decltype(nums)>::size_type nums_idx{};
        for (size_t bucket_idx = 0; range > bucket_idx; ++bucket_idx) {
            for (auto count = bucket[bucket_idx]; 0 < count; --count) {
                nums[nums_idx++] = bucket_idx;
            }
        }
    }
    
    void sortColors(vector<int>& nums) {
        sortColors_bucketSort(nums);
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

struct elapsed_time_t
{
    std::chrono::steady_clock::time_point start{};
    std::chrono::steady_clock::time_point end{};
    
    elapsed_time_t(
        std::chrono::steady_clock::time_point start
        , std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now()
    ) : start{std::move(start)}, end{std::move(end)} {}
};

std::ostream&
operator<<(std::ostream& os, elapsed_time_t const& et)
{
    auto const elapsed_time = et.end - et.start;
    os << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count()
       << '.' << (std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count() % 1000)
       << " ms";
    return os;
}

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<int> value{2,0,2,1,1,0};
    auto const expected = [&]{ auto expected = value; std::sort(expected.begin(), expected.end()); return expected; }();
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        Solution{}.sortColors(value);
        CHECK(expected == value);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

TEST_CASE("Case 2")
{
    cerr << "Case 1" << '\n';
    vector<int> value{2,0,1};
    auto const expected = [&]{ auto expected = value; std::sort(expected.begin(), expected.end()); return expected; }();
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        Solution{}.sortColors(value);
        CHECK(expected == value);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

/*
    End of "main.cpp"
*/