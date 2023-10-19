////
//// Created by Nik  on 17.10.23.
////
//
//#include <iostream>
//#include <vector>
//#include <cmath>
//
//
//std::vector<float> func2(
//        float t,
//        std::vector<float>* y
//) {
//
//    return std::vector<float> {
//            y->at(0),
//            exp(-t * y->at(0))
//    };
//}
//
//
//std::vector<std::vector<float>> euler(
//        std::vector<float> (*func) (float, std::vector<float>*),
//        float x0,
//        float xf,
//        std::vector<float>* y0,
//        float h
//) {
//
//    int count = (int) ((xf - x0) / h) + 1;
//    std::vector<std::vector<float>> y {*y0};
//    int len = y0->size();
//    float x = x0;
//
//    for (int i = 1; i < count; i++) {
//        std::vector<float> right_parts, curr;
//        right_parts = func2(x, &y[i-1]);
//
//        for (int j = 0; j < len; j++) {
//            curr.push_back(y[i-1][j] + h * right_parts[j]);
//        }
//
//        y.push_back(curr);
//        x += h;
//    }
//
//    return y;
//}
//
//
//int main1() {
//    std::vector<float> y0 {0, 0};
//    std::vector<std::vector<float>> ans = euler(&func2, 0, 1, &y0, 0.1);
//    for (int i = 0; i < ans.size(); i++) {
//        for (int j = 0; j < ans[i].size(); j++) {
//            std::cout << ans[i][j] << " ";
//        }
//        std::cout << "\n";
//    }
//    return 0;
//}
/*
0 0
0.0825205 0.0967883
0.164409 0.188581
0.244691 0.275197
0.322563 0.356625
0.397418 0.432996
0.468849 0.504551
0.536635 0.571618
0.600725 0.634589
0.661205 0.6939
0.718266 0.750009 */