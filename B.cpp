#include "C.h"
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("除数不能为零！");
    }
    return a / b;
}

void doCalculate(HWND hwnd, char op) {
    char buf1[64], buf2[64];
    GetDlgItemText(hwnd, 101, buf1, sizeof(buf1));
    GetDlgItemText(hwnd, 102, buf2, sizeof(buf2));

    double a = atof(buf1);
    double b = atof(buf2);
    double result = 0;

    try {
        switch (op) {
            case '+': result = add(a, b); break;
            case '-': result = subtract(a, b); break;
            case '*': result = multiply(a, b); break;
            case '/': result = divide(a, b); break;
        }
        char bufResult[64];
        sprintf(bufResult, "%g", result);
        SetDlgItemText(hwnd, 103, bufResult);
    } catch (const std::exception& e) {
        SetDlgItemText(hwnd, 103, e.what());
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "第一个数:", WS_CHILD | WS_VISIBLE,
                         30, 30, 80, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "第二个数:", WS_CHILD | WS_VISIBLE,
                         30, 70, 80, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "结    果:", WS_CHILD | WS_VISIBLE,
                         30, 160, 80, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                         120, 28, 180, 25, hwnd, (HMENU)101, NULL, NULL);
            CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                         120, 68, 180, 25, hwnd, (HMENU)102, NULL, NULL);
            CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                         120, 158, 180, 25, hwnd, (HMENU)103, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
                         40, 110, 70, 35, hwnd, (HMENU)201, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
                         120, 110, 70, 35, hwnd, (HMENU)202, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
                         200, 110, 70, 35, hwnd, (HMENU)203, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
                         280, 110, 70, 35, hwnd, (HMENU)204, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id == 201) doCalculate(hwnd, '+');
            else if (id == 202) doCalculate(hwnd, '-');
            else if (id == 203) doCalculate(hwnd, '*');
            else if (id == 204) doCalculate(hwnd, '/');
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}