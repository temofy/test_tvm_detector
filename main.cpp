#include <iostream>
// #include "json.hpp"
#include <fstream>
#include <tvm/runtime/module.h>
#include <tvm/runtime/registry.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

class TVM_Detector
{
public:
    TVM_Detector(string model_dir="model/", string model_name="mod")
    {
		tvm::runtime::Module mod_syslib = tvm::runtime::Module::LoadFromFile(model_dir + model_name + ".so");

		std::ifstream json_in(model_dir + model_name + ".json", std::ios::in);
		std::string json_data((std::istreambuf_iterator<char>(json_in)), std::istreambuf_iterator<char>());
		json_in.close();

		std::ifstream params_in(model_dir + model_name + ".params", std::ios::binary);
		std::string params_data((std::istreambuf_iterator<char>(params_in)), std::istreambuf_iterator<char>());
		params_in.close();

		auto graph_runtime = tvm::runtime::Registry::Get("tvm.graph_runtime.create");
		if (graph_runtime == nullptr) {
			cerr << "Graph Runtime пустой" << endl;
			throw "Graph Runtime Empty";
		}
		//tvm::runtime::Module mod = (*tvm::runtime::Registry::Get("tvm.graph_runtime.create"))(json_data, mod_syslib, 0, 0);
    }
};

int main(int args, char **argv)
{
	if (args != 2)
	{
		cout << "Введите путь до файла .mp4 или .jpg" << endl;
		return 0;
	}
	auto detector = TVM_Detector("model/", "mod");

	string path(argv[1]);
	if (path.find(".jpg") != string::npos)
	{
		Mat image = imread(path);
		if (!image.empty())
		{
			imshow("Изображение", image);
			waitKey();
		}
		else {
			cout << "Пустое изображение" << endl;
			return -1;
		}
	}
	else if (path.find(".mp4") != string::npos)
	{
		VideoCapture cap(path);

		if (!cap.isOpened()) {
			cout << "Ошибка открытия видео" << endl;
			return -1;
		}
		while (1)
		{
			Mat frame;
			cap >> frame;
			if (frame.empty())
				break;
			
			imshow("Видео", frame);
			int key = waitKey(1);
			if (key == 27)
				break;
		}
		cap.release();
		destroyAllWindows();
	}


    return 0;
}
