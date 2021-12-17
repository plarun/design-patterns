package main

import "fmt"

type server interface {
	handleRequest(string, string) (int, string)
}

type application struct{}

func (app *application) handleRequest(url, method string) (int, string) {
	if url == "/app/status" && method == "GET" {
		return 200, "Ok"
	}
	if url == "/create/user" && method == "POST" {
		return 201, "User Created"
	}
	return 404, "Not Ok"
}

type proxyServer struct {
	application       *application
	maxAllowedRequest int
	rateLimiter       map[string]int
}

func newProxyServer() *proxyServer {
	return &proxyServer{
		application:       &application{},
		maxAllowedRequest: 2,
		rateLimiter:       make(map[string]int),
	}
}

func (proxy *proxyServer) checkRateLimiting(url string) bool {
	if proxy.rateLimiter[url] > proxy.maxAllowedRequest {
		return false
	}
	proxy.rateLimiter[url] = proxy.rateLimiter[url] + 1
	return true
}

func (proxy *proxyServer) handleRequest(url, method string) (int, string) {
	allowed := proxy.checkRateLimiting(url)
	if !allowed {
		return 403, "Not Allowed"
	}
	return proxy.application.handleRequest(url, method)
}

func printStatus(url string, httpStatusCode int, body string) {
	fmt.Printf("\nUrl: %s\nHttpCode: %d\nBody: %s\n", url, httpStatusCode, body)
}

func app(proxy server) {
	statusURL := "/app/status"
	createURL := "/create/user"

	httpStatusCode, body := proxy.handleRequest(statusURL, "GET")
	printStatus(statusURL, httpStatusCode, body)
	httpStatusCode, body = proxy.handleRequest(statusURL, "GET")
	printStatus(statusURL, httpStatusCode, body)
	httpStatusCode, body = proxy.handleRequest(statusURL, "GET")
	printStatus(statusURL, httpStatusCode, body)
	httpStatusCode, body = proxy.handleRequest(createURL, "POST")
	printStatus(createURL, httpStatusCode, body)
	httpStatusCode, body = proxy.handleRequest(createURL, "GET")
	printStatus(createURL, httpStatusCode, body)
}

func main() {
	proxy := newProxyServer()
	app(proxy)
}
