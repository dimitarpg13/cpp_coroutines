// coro_ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>

struct ReturnObject {
	struct promise_type {
		ReturnObject get_return_object() { return {}; }
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void unhandled_exception() {}
		void return_void() {};
	};
};

struct Awaiter {
	std::coroutine_handle<>* hp_;
	constexpr bool await_ready() const noexcept { return false; }
	void await_suspend(std::coroutine_handle<> h) { *hp_ = h; }
	constexpr void await_resume() const noexcept {}
};

ReturnObject 
counter(std::coroutine_handle<>* continuation_out)
{
	Awaiter a{ continuation_out };
	for (unsigned i = 0;; ++i) {
		co_await a;
		std::cout << "counter: " << i << std::endl;
	}
}

void main1() {
	std::coroutine_handle<> h;
	counter(&h);
	for (int i = 0; i < 3; ++i) {
		std::cout << "In main1 function\n";
		h();
	}
	h.destroy();
}

int main(const int argc, const char* argv[]) {
	main1();
	return 0;
}
