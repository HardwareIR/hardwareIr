#pragma once

#include <atomic>
#include <netlistDB/netlist.h>
#include <netlistDB/utils/thread_pool.h>

namespace netlistDB {
namespace query {

/*
 * Traverse nodes in circuit
 **/
class NETLISTDB_PUBLIC QueryTraverse {
public:
	// align to cache line does not bring perf. improvement
	// as there is large number of nodes and the access is more or less random.
	// [TODO] how is this possible?
	using flag_t = bool;
	using atomic_flag_t = std::atomic<flag_t>;

	// the function which calls the argument function on children of the i node
	using callback_t = std::function<void(iNode&, const std::function<void(iNode &)> &)>;
	atomic_flag_t * visited;
	bool visited_clean;
	size_t load_balance_limit;
	const callback_t * callback;
	size_t max_items;
	utils::ThreadPool thread_pool;

	QueryTraverse(size_t max_items);

	inline bool is_visited(iNode &n) {
		//return visited[n.index].exchange(true);
		return visited[n.index].exchange(true);
	}

	static void dummy_callback(iNode &n, const std::function<void(iNode &)> & select);
public:
	/*
	 * Reset visit flags used in traversal
	 * */
	void clean_visit_flags();

	/*
	 * Traverse graph from starts and call callback on each node exactly once
	 * @param starts the nodes where the search should start
	 * @param callback the callback function called on each visited node (exactly once)
	 * */
	void traverse(std::vector<iNode*> starts, const callback_t & callback);

	~QueryTraverse();
protected:
	/*
	 * Traverse using limited DFS, if limit is exceeded the rest children are processed
	 * new task
	 *
	 * @param n node to process
	 * */
	void traverse(iNode & n);
};

}
}
