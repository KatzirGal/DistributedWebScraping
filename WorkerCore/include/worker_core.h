#include <vector>
#include <string>

#include <Poco/URI.h>
#include <Poco/Util/ServerApplication.h>

class WorkerCore : public Poco::Util::ServerApplication
{
public:
	WorkerCore();
	~WorkerCore();

protected:
	int main(const std::vector<std::string>& argv) override;

private:
	int StartServer();

private:

};