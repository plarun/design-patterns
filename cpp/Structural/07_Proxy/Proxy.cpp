#include <iostream>
#include <unordered_map>
#include <random>
#include <thread>
#include <stdexcept>


/*
Type: Structural
Pattern: Proxy

Rrovides a substitute or placeholder for another object. 
A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

Access control (protection proxy). This is when you want only specific clients to be able to use the service object; 
	for instance, when your objects are crucial parts of an operating system and clients are various launched applications (including malicious ones).
Local execution of a remote service (remote proxy). This is when the service object is located on a remote server.
Logging requests (logging proxy). This is when you want to keep a history of requests to the service object.
Caching request results (caching proxy). 
	This is when you need to cache results of client requests and manage the life cycle of this cache, especially if results are quite large.
Smart reference. This is when you need to be able to dismiss a heavyweight object once there are no clients that use it.

*/

class Video {
	public:
		std::string name;
		int duration;

		Video(std::string _name, int _dur): name(_name), duration(_dur) {}
};

// interface
class ThirdPartyYoutubeLib {
	public:
		virtual std::unordered_map<std::string, Video*> popularVideos() = 0;

		virtual Video* getVideo(const std::string videoId) const = 0;
};

class ThirdPartyYoutubeClass : public ThirdPartyYoutubeLib {
	public:
		ThirdPartyYoutubeClass() {
			videos.insert(std::make_pair("v1", new Video("v1", 2*60)));
			videos.insert(std::make_pair("v2", new Video("v2", 3*60)));
			videos.insert(std::make_pair("v3", new Video("v3", 1*60)));
			videos.insert(std::make_pair("v4", new Video("v4", 30)));
			videos.insert(std::make_pair("v5", new Video("v5", 60)));
		}

		std::unordered_map<std::string, Video*> popularVideos() override {
			connectToServer("http://www.youtube.com");
			return getRandomVideos();
		}
		
		Video* getVideo(const std::string videoId) const override {
			connectToServer("http://www.youtube.com/" + videoId);
			return getSomeVideo(videoId);
		}

	private:
		std::unordered_map<std::string, Video*> videos;

		int random(int min, int max) const {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distro(min, max);
			return distro(gen);
		}

		void experienceNetworkLatency() const {
			int randomLat = random(5, 10);
			for (int i=0; i<randomLat; ++i) {
				try {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				} catch (std::exception& e) {
					std::cout << "interrupted" << std::endl;
				}
			}
		}

		void connectToServer(const std::string server) const {
			std::cout << "Connecting to server " << server << "...\n";
			experienceNetworkLatency();
			std::cout << "Connected\n";
		}

		std::unordered_map<std::string, Video*> getRandomVideos() const {
			experienceNetworkLatency();
			return videos;
		}

		Video* getSomeVideo(const std::string videoId) const {
			experienceNetworkLatency();
			if (videos.find(videoId) != videos.end())
				return videos.at(videoId);
			return nullptr;
		}
};