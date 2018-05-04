#include <iostream>
#include <netlib/lapacke.h>

int main() {
  double matrix[2][2] = {{5, 2}, {2, 5}};
  std::cout << "factorize {{5, 2}, {2, 5}}\n";
  int result = LAPACKE_dpotrf(LAPACK_ROW_MAJOR, 'L', 2, (double*)matrix, 2);
  if (result != 0) {
    std::cerr << "Failed to factorize\n";
  }
  std::cout << "result {{" << matrix[0][0] << ", " << 0 << "}, "
            << "{" << matrix[1][0] << ", " << matrix[1][1] << "}}\n";
  return 0;
}
