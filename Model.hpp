#pragma once
#include "bits/stdc++.h"
#include "Layer.hpp"
#include "Loss.hpp"
#include "Activation.hpp"

class NNModel{
public:
    // mse : mean squared error
    // cen : mean cross-entropy error

    int m_input_size, m_output_size;
    std::vector<Layers::Dense>model;
    std::string m_loss;
    std::vector<std::vector<double>> diff_error; // 相対誤差。maeとしても使えるけど、今回は二乗誤差の逆伝播(絶対値)、softmaxの逆伝播(そのまま)に使う
    std::string m_optimizer;

    bool compiled;

    const double RMSProp_beta = 0.9;
    const double Momentum_alpha = 0.9;

    // 損失関数がエントロピーなら最後のレイヤーの活性化関数はsoftmaxなので、何もしない
    // そうでない場合は一度損失関数を通して逆伝播させる

// public:
    NNModel();
    NNModel(int input_size);
    void AddDenseLayer(int unit, ActivationType activation);
    std::vector<std::vector<double>> predict(const std::vector<std::vector<double>>&data);
    void backward();
    std::vector<std::vector<double>> numerical_gradient_layer(std::vector<std::vector<double>>&batch_x, std::vector<std::vector<double>>&batch_y, int x);
    std::vector<double> numerical_gradient_bias(std::vector<std::vector<double>>&batch_x, std::vector<std::vector<double>>&batch_y, int x);
    std::vector<double> fit(int step, double learning_rate, std::vector<std::vector<double>>&x, std::vector<std::vector<double>>&y, int batch_size, std::string loss);
    void compile(std::string optimizer);
    double caluculate_loss(std::vector<std::vector<double>>&batch_x, std::vector<std::vector<double>>&batch_y);
    void print();
};
