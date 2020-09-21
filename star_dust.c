// Chivereanu Radu-Gabriel, 315 CA
#include <stdio.h>
#include <stdlib.h>
double task1(int n, int* b_m, char** byte_mat);
void task2(int** b_m, char*** byte_mat);
void reforge(int* b_m, char** initial_map, int n);
void fill(char** byte_mat, int n, int* b_m);
int main() {
  int n, m, i, j, cnt, *b_m, hexa, k;
  char** byte_mat;
  char* bytes;
  double m_a;
  scanf("%d", &n);
  byte_mat = (char**)malloc(n * sizeof(int*));
  b_m = (int*)malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    scanf("%d ", &m);
    byte_mat[i] = (char*)malloc(m * sizeof(int));
    cnt = 0;
    for (j = 0; j < m; j++) {
      scanf("%X", &hexa);
      bytes = (char*)&hexa;
      for (k = 0; k < 4; k++) {
        byte_mat[i][cnt++] = bytes[k];
      }
    }
    b_m[i] = cnt;
  }
  m_a = task1(n, b_m, byte_mat);
  task2(&b_m, &byte_mat);
  printf("task 1\n");
  printf("%.8lf\n", m_a);
  printf("task 2\n");
  reforge(b_m, byte_mat, n);
  printf("task 3\n");
  fill(byte_mat, n, b_m);
  for (i = 0; i < n; i++) {
    free(byte_mat[i]);
  }
  free(byte_mat);
  free(b_m);
  return 0;
}
double task1(int n, int* b_m, char** byte_mat) {
  int i;
  int nr_bytes = 0;
  int sum_bytes = 0;
  for (i = 0; i < b_m[0]; i++) {
    nr_bytes++;
    sum_bytes += byte_mat[0][i];
  }
  for (i = 1; i < n - 1; i++) {
    nr_bytes++;
    sum_bytes += byte_mat[i][b_m[i] - 1];
  }
  for (i = 0; i < b_m[n - 1]; i++) {
    nr_bytes++;
    sum_bytes += byte_mat[n - 1][i];
  }
  for (i = n - 2; i >= 1; i--) {
    nr_bytes++;
    sum_bytes += byte_mat[i][0];
  }
  return ((double)sum_bytes / (double)nr_bytes);
}
void transform_index(char command, char type, int* index) {
  if (command == 'S') {
    *index = *index + 1;
  }
  if (type == 'S') {
    *index = (*index - 1) * 2;
  }
  if (type == 'I') {
    *index = (*index - 1) * 4;
  }
  if (type == 'C') {
    *index = *index - 1;
  }
}
void task2(int** b_m, char*** byte_mat) {
  int k, op = 0, line, index, j, aux, outof;
  int value, it;
  char command, type, new_liner;
  char* bytes;
  scanf("%d ", &k);
  for (op = 1; op <= k; op++) {
    scanf("%c %c %d %d", &command, &type, &line, &index);
    if (type == 'S') {
      outof = index * sizeof(short int);
    }
    if (type == 'I') {
      outof = index * sizeof(int);
    }
    if (type == 'C') {
      outof = index * sizeof(char);
    }
    transform_index(command, type, &index);
    if (command == 'M') {
      scanf("%X%c", &value, &new_liner);
      bytes = (char*)&value;
      if (outof >= (*b_m)[line]) {
        (*byte_mat)[line] = (char*)realloc((*byte_mat)[line], outof);
        for (j = (*b_m)[line]; j < outof; j++) {
          (*byte_mat)[line][j] = 0;
        }
        (*b_m)[line] = outof;
      }
      if (type == 'S') {
        (*byte_mat)[line][index] = bytes[0];
        (*byte_mat)[line][index + 1] = bytes[1];
      } else if (type == 'I') {
        (*byte_mat)[line][index] = bytes[0];
        (*byte_mat)[line][index + 1] = bytes[1];
        (*byte_mat)[line][index + 2] = bytes[2];
        (*byte_mat)[line][index + 3] = bytes[3];
      } else {
        (*byte_mat)[line][index] = value;
      }
    }
    if (command == 'S') {
      scanf("%c", &new_liner);
      if (type == 'I') {
        for (it = 0; it <= 1; it++) {
          aux = (*byte_mat)[line][index + it];
          (*byte_mat)[line][index + it] = (*byte_mat)[line][index + 3 - it];
          (*byte_mat)[line][index + 3 - it] = aux;
        }
      } else if (type == 'S') {
        aux = (*byte_mat)[line][index];
        (*byte_mat)[line][index] = (*byte_mat)[line][index + 1];
        (*byte_mat)[line][index + 1] = aux;
      }
    }
    if (command == 'D') {
      scanf("%c", &new_liner);
      if (type == 'I') {
        for (it = index; it <= index + 3; it++) {
          (*byte_mat)[line][it] = 0;
        }
      } else if (type == 'S') {
        for (it = index; it <= index + 1; it++) {
          (*byte_mat)[line][it] = 0;
        }
      } else {
        (*byte_mat)[line][index] = 0;
      }
    }
  }
}
void reforge(int* b_m, char** initial_map, int n) {
  int i, j;
  int* integer;
  for (i = 0; i < n; i++, printf("\n")) {
    for (j = 0; j < b_m[i]; j += 4) {
      integer = (int*)&initial_map[i][j];
      printf("%08X ", integer[0]);
    }
  }
}
void fill(char** byte_mat, int n, int* b_m) {
  int i;
  int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
  int *qx, *qy, x, y, ans, cnt, j, k, maxim = 0, ansx, ansy, px, py;
  qx = (int*)malloc(0);
  qy = (int*)malloc(0);
  for (i = 0; i < n; i++) {
    for (j = 0; j < b_m[i]; j++) {
      if (byte_mat[i][j] == 0) {
        cnt = 0;
        ans = 1;
        qx = (int*)realloc(qx, ++cnt * sizeof(int));
        qy = (int*)realloc(qy, cnt * sizeof(int));
        qx[cnt - 1] = i;
        qy[cnt - 1] = j;
        byte_mat[i][j] = 1;
        while (cnt) {
          x = qx[cnt - 1];
          y = qy[cnt - 1];
          cnt--;
          for (k = 0; k < 4; k++) {
            px = x + dx[k];
            py = y + dy[k];
            if (px < n && px >= 0 && py < b_m[px] && py >= 0 &&
                byte_mat[px][py] == 0) {
              qx = (int*)realloc(qx, ++cnt * sizeof(int));
              qy = (int*)realloc(qy, cnt * sizeof(int));
              qx[cnt - 1] = px;
              qy[cnt - 1] = py;
              byte_mat[px][py] = 1;
              ans++;
            }
          }
        }
        if (ans > maxim) {
          maxim = ans;
          ansx = i;
          ansy = j;
        }
      }
    }
  }
  printf("%d %d %d\n", ansx, ansy, maxim);
  free(qx);
  free(qy);
}
