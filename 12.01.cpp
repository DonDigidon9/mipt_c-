#include <cstdio>
int main() {
  const char* s = "#include <cstdio>%cint main() {%c  const char* s = %c%s%c;%c  printf(s, 10, 10, 10, 34, s, 34, 10, 10, 10, 10);%c}%c%c";
  printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10);
}
