package main

import "fmt"

type evictionAlgo interface {
	evict(c *cache)
}

type fifo struct{}

func (algo *fifo) evict(cache *cache) {
	fmt.Println("evict by fifo strategy")
}

type lru struct{}

func (algo *lru) evict(cache *cache) {
	fmt.Println("evict by lru strategy")
}

type lfu struct{}

func (algo *lfu) evict(cache *cache) {
	fmt.Println("evict by lfu strategy")
}

type cache struct {
	storage      map[string]string
	evictionAlgo evictionAlgo
	capacity     int
	maxCapacity  int
}

func initCache(algo evictionAlgo) *cache {
	return &cache{
		storage:      make(map[string]string),
		evictionAlgo: algo,
		capacity:     0,
		maxCapacity:  2,
	}
}

func (cache *cache) setEvictionAlgo(algo evictionAlgo) {
	cache.evictionAlgo = algo
}

func (cache *cache) add(key, value string) {
	if cache.capacity == cache.maxCapacity {
		cache.evict()
	}
	cache.capacity++
	cache.storage[key] = value
}

func (cache *cache) evict() {
	cache.evictionAlgo.evict(cache)
	cache.capacity--
}

func app() {
	lfu := &lfu{}
	cache := initCache(lfu)

	cache.add("a", "97")
	cache.add("b", "98")
	cache.add("c", "99")

	lru := &lru{}
	cache.setEvictionAlgo(lru)

	cache.add("d", "100")

	fifo := &fifo{}
	cache.setEvictionAlgo(fifo)

	cache.add("e", "101")
}

func main() {
	app()
}
