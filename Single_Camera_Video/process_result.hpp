/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <iostream>
#include <fstream>

/*
 *   The color loops every 27 times,
 *    because each channel of RGB loop in sequence of "0, 127, 254"
 */

static cv::Scalar getColor(int label) {
  int c[3];
  for (int i = 1, j = 0; i <= 9; i *= 3, j++) {
    c[j] = ((label / i) % 3) * 127;
  }
  return cv::Scalar(c[2], c[1], c[0]);
}

using namespace std;
static cv::Mat process_result(cv::Mat &image,
                              const vitis::ai::YOLOv3Result &result,
                              bool is_jpeg) {
   const char *labels_txt[7] = {"stand", "sit", "fall", "transition", "chair", "bed", "table"};
   cv::resize(image,image,cv::Size(720,720));
   ofstream myfile;
   myfile.open("test_sms.txt", ios::app);
   for (const auto bbox : result.bboxes) {
    int label = bbox.label;
    float xmin = bbox.x * image.cols + 1;
    float ymin = bbox.y * image.rows + 1;
    float xmax = xmin + bbox.width * image.cols;
    float ymax = ymin + bbox.height * image.rows;
    float confidence = bbox.score;
    if (xmax > image.cols)
      xmax = image.cols;
    if (ymax > image.rows)
      ymax = image.rows;
    LOG_IF(INFO, is_jpeg) << "RESULT: " << label << "\t" << xmin << "\t" << ymin
                          << "\t" << xmax << "\t" << ymax << "\t" << confidence
                          << "\n";
    cv::rectangle(image, cv::Point(xmin, ymin-0.2), cv::Point(xmax, ymax),
                  getColor(label), 1, 1, 0);
    cv::putText(image,labels_txt[label],cv::Point(xmin,ymin),cv::FONT_HERSHEY_TRIPLEX,0.5,getColor(label),2);
  
  if(label == 2)
  	myfile << "Fall detected\n";
   }
  myfile.close();
  return image;
}
