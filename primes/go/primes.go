package main

import "fmt"

func Go() {
	for i := 0; i < 50000; i++ {
		var comp = 0
		for j := 2; j < i; j++ {
			f := float32(i)
			rf := f / float32(j)
			r := i / j
			ri := r
			if rf == float32(ri) {
				comp = 1
				break
			}
		}
		if comp == 0 {
			fmt.Println(i, " -- gomple")
		}
	}
}

func main() {
	Go()
}
