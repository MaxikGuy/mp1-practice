#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <tchar.h>
#include <windows.h>

typedef unsigned long long	ull;
typedef long long			ll;
typedef unsigned int		uint;

WIN32_FIND_DATA names[MAX_PATH];
WIN32_FIND_DATA File;
HANDLE hfile;

void input() {
	char* a = (char*)malloc(MAX_PATH);
	wchar_t* path = (wchar_t*)malloc(MAX_PATH * sizeof(wchar_t));
	do {
		printf("Введите путь в папку: \n");
		scanf("%s", a);
		strcat(a, "\\*.*");
		mbstowcs(path, a, strlen(a) + 1);
		hfile = FindFirstFileW(path, &File);
	} while (hfile == INVALID_HANDLE_VALUE);
	system("cls");
	printf("Путь: %s \n", a);
	free(a);
	free(path);
}

void arr_null(ull* a, uint n) {
	uint i;
	for (i = 0; i < n; i++)
		a[i] = 0;
}

void arr_minus(ll* a, uint n) {
	uint i;
	for (i = 0; i < n; i++)
		a[i] = -1;
}

void arr_copy(ull* a, ull* a_copy, uint n) {
	int i;
	for (i = 0; i < n; i++)
		a_copy[i] = a[i];
}

void swap(ull* a, ull* b) { // swap(&a, &b);
	ull tmp = *a;
	*a = *b;
	*b = tmp;
}

// Сортировки:
// Сортировка выбора
void choose_sort(ull* a, uint n, int mode) {
	if (mode == 0) {  // increase
		uint i, j, id;
		ull min;
		for (i = 0; i < n; i++) {
			min = a[i];
			id = i;
			for (j = i + 1; j < n; j++) {
				if (a[j] < min) {
					min = a[j];
					id = j;
				}
			}
			swap(&a[id], &a[i]);
		}
	}
	if (mode == -1) { // decrease
		uint i, j, id;
		ull max;
		for (i = 0; i < n; i++) {
			max = a[i];
			id = i;
			for (j = i + 1; j < n; j++) {
				if (a[j] > max) {
					max = a[j];
					id = j;
				}
			}
			swap(&a[id], &a[i]);
		}
	}
}

// Сортировка вставками
void insert_sort(ull* a, uint n, int mode) {
	if (mode == 0) {  // increase
		uint i, j;
		ull tmp;
		for (i = 1; i < n; i++) {
			tmp = a[i];
			j = i - 1;
			while ((j >= 0) && (a[j] > tmp)) {
				swap(&a[j + 1], &a[j]);
				j--;
			}
		}
	}
	if (mode == -1) { // decrease
		uint i, j;
		ull tmp;
		for (i = 1; i < n; i++) {
			tmp = a[i];
			j = i - 1;
			while ((j >= 0) && (a[j] < tmp)) {
				swap(&a[j + 1], &a[j]);
				j--;
			}
		}
	}
}

// Сортировка "пузырьком"
void bubble_sort(ull* a, uint n, int mode) { // РАБОТАЕТ НЕ ПРАВИЛЬНО!!!
	if (mode == 0) {  // increase
		uint i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n - i - 1; j++) {
				if (a[j + 1] < a[j])
					swap(&a[j], &a[j + 1]);
			}
		}
	}
	if (mode == -1) { // decrease
		uint i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n - i - 1; j++) {
				if (a[j + 1] > a[j])
					swap(&a[j], &a[j + 1]);
			}
		}
	}
}

// Сортировка слиянием
void merge_increase(ull* a, uint left, uint mid, uint right) {
	uint i = left, j = mid + 1, k = 0;
	ull* c;
	c = (ull*)malloc((right - left + 1) * sizeof(ull));
	while ((i <= mid) && (j <= right)) {
		if (a[i] < a[j])
			c[k++] = a[i++];
		else
			c[k++] = a[j++];
	}

	if (i > mid)
		while (j <= right)
			c[k++] = a[j++];
	else
		while (i <= mid)
			c[k++] = a[i++];

	for (i = left; i <= right; i++)
		a[i] = c[i - left];
	free(c);
}
void merge_decrease(ull* a, uint left, uint mid, uint right) {
	uint i = left, j = mid + 1, k = 0;
	ull* c;
	c = (ull*)malloc((right - left + 1) * sizeof(ull));
	while ((i <= mid) && (j <= right)) {
		if (a[i] > a[j])
			c[k++] = a[i++];
		else
			c[k++] = a[j++];
	}

	if (i > mid)
		while (j <= right)
			c[k++] = a[j++];
	else
		while (i <= mid)
			c[k++] = a[i++];

	for (i = left; i <= right; i++)
		a[i] = c[i - left];
	free(c);
}
void merge_sort_lr(ull* a, uint left, uint right, int mode) { // increase // decrease
	if (left == right)
		return;
	uint mid = (left + right) / 2;
	merge_sort_lr(a, left, mid, mode);
	merge_sort_lr(a, mid + 1, right, mode);
	if (mode == 0)
		merge_increase(a, left, mid, right);
	if (mode == -1)
		merge_decrease(a, left, mid, right);
}
void merge_sort(ull* a, uint n, int mode) {
	if ((mode != 0) && (mode != -1)) return;
	merge_sort_lr(a, 0, n - 1, mode);
}

// Быстрая сортировка
void quick_sort_increase(ull* a, uint low, uint high) {
	ull mid;
	ull l = low, h = high;
	mid = a[(l + h) / 2];
	while (l < h) {
		while (a[l] < mid)
			l++;
		while (a[h] > mid)
			h--;
		if (l <= h) {
			swap(&a[l], &a[h]);
			l++;
			h--;
		}
	}
	if (low < h)
		quick_sort_increase(a, low, h);
	if (l < high)
		quick_sort_increase(a, l, high);
}
void quick_sort_decrease(ull* a, uint low, uint high) {
	uint mid;
	uint l = low, h = high;
	mid = a[(l + h) / 2];
	while (l < h) {
		while (a[l] > mid)
			l++;
		while (a[h] < mid)
			h--;
		if (l <= h) {
			swap(&a[l], &a[h]);
			l++;
			h--;
		}
	}
	if (low < h)
		quick_sort_decrease(a, low, h);
	if (l < high)
		quick_sort_decrease(a, l, high);
}
void quick_sort(ull* a, uint n, int mode) {
	if (mode == 0)  quick_sort_increase(a, 0, n - 1);
	if (mode == -1) quick_sort_decrease(a, 0, n - 1);
}

int if_a_in_b(ll a, ll* b, uint n) {
	uint i;
	for (i = 0; i < n; i++)
		if (a == b[i])
			return 1;
	return 0;
}

ll index(ull* arr, ull* source, ll* indexes, uint n, uint k) {
	ll i, ind;
	for (i = 0; i < n; i++) 
		if (arr[k] == source[i]) {
			ind = i;
			if (if_a_in_b(ind, indexes, n))
				continue;
			else
				break;
		}
	return ind;
}

void menu() {
	printf("\n============================================================\n\n");
	printf("Укажите номер опции, которую вы хотите применить:\n");
	printf("1. Ввести другой путь до директории\n");
	printf("2. Вывести файлы и их размер\n");
	printf("3. Отсортировать файлы\n");
	printf("0. Выход\n\n");

}

void menu_sortings(int mode) {
	printf("\n============================================================\n\n");
	printf("Выберите сортировку:\n");
	printf("1. Сортировка выбора\n");
	printf("2. Сортировка вставками\n");
	printf("3. Сортировка \"пузырьком\"\n");
	printf("4. Сортировка слиянием\n");
	printf("5. Быстрая сортировка\n\n");
	if (mode == 0)
		printf("6. Сортировка по: возрастанию\n");
	if (mode == -1)
		printf("6. Сортировка по: убыванию\n");
	printf("0. Назад\n\n");
}

int main() {
	setlocale(LC_ALL, "rus");
	uint i = 0, N = 0;
	int inp, srt, mode = 0;
	float timer;
	clock_t start_timer, end_timer;
	ull* size = (ull*)malloc(MAX_PATH * sizeof(ull));
	ull* arr = (ull*)malloc(MAX_PATH * sizeof(ull));
	ll* indexes = (ll*)malloc(MAX_PATH * sizeof(ll));
	wchar_t** fname = (wchar_t**)malloc(MAX_PATH * sizeof(wchar_t*));
	for (i = 0; i < MAX_PATH; i++) {
		fname[i] = (wchar_t*)malloc(200 * sizeof(wchar_t));
		fname[i] = L" ";
	}

	input();
	i = 0;
	do {
		if (i == 0 || i == 1) {
			i++;
			continue;
		}
		names[i] = File;
		fname[i-2] = names[i].cFileName;
		size[i-2] = names[i].nFileSizeLow;
		i++;
		N++;
	} while (FindNextFileW(hfile, &File) != NULL);
	
	while (1) {
		start:
		menu();
		do {
			scanf("%d", &inp);
		} while (inp < 0 || inp > 3);
		if (inp == 0) break;
		if (inp == 1) {
			system("cls");
			arr_null(size, MAX_PATH);
			arr_null(arr, MAX_PATH);
			input();
			i = 0;
			N = 0;
			do {
				if (i == 0 || i == 1) {
					i++;
					continue;
				}
				names[i] = File;
				fname[i-2] = names[i].cFileName;
				size[i-2] = names[i].nFileSizeLow;
				i++;
				N++;
			} while (FindNextFileW(hfile, &File) != NULL);
			goto start;
		}
		if (inp == 2) {
			system("cls");
			printf("Данные в вашей директории: \n");
			printf("Имя: %50c Размер(байт)\n", ' ');
			for (i = 0; i < N; i++) {
				printf("\n%-60S", fname[i]);
				if (size[i] == 0)
					printf("Папка (размер неизвестен)\n");
				else
					printf("%d \n", size[i]);
			}
			goto start;
		}
		if (inp == 3) {
			start_sort:
			system("cls");
			menu_sortings(mode);
			do {
				scanf("%d", &srt);
			} while (srt < 0 || srt > 6);
			
			if (srt == 0) goto start;
			
			if (srt == 6) {
				if (mode == 0)
					mode = -1;
				else
					mode = 0;
				goto start_sort;
			}

			arr_copy(size, arr, N);
			if (srt == 1) {
				start_timer = clock();
				choose_sort(arr, N, mode);
				end_timer = clock();
				timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
			}
			
			if (srt == 2) {
				start_timer = clock();
				insert_sort(arr, N, mode);
				end_timer = clock();
				timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
			}
			
			if (srt == 3) {
				start_timer = clock();
				bubble_sort(arr, N, mode);
				end_timer = clock();
				timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
			}
			
			if (srt == 4) {
				start_timer = clock();
				merge_sort(arr, N, mode);
				end_timer = clock();
				timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
			}
			
			if (srt == 5) {
				start_timer = clock();
				quick_sort(arr, N, mode);
				end_timer = clock();
				timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
			}

			arr_minus(indexes, N);
			for (i = 0; i < N; i++) {
				indexes[i] = index(arr, size, indexes, N, i);
			}
			system("cls");
			for (i = 0; i < N; i++) {
				printf("Имя: %50c Размер(байт)\n", ' ');
				for (i = 0; i < N; i++) {
					printf("\n%-60S", fname[indexes[i]]);
					if (size[indexes[i]] == 0)
						printf("Папка (размер неизвестен)\n");
					else
						printf("%d \n", size[indexes[i]]);
				}
			}
			printf("\nВремя сортировки: %f сек.\n", timer);

			printf("\nВыбрать другую сортировку / Вернуться назад\n(1/0)\n");
			do {
				scanf("%d", &inp);
			} while ((inp < 0) || (inp > 1));
			if (inp == 1) { system("cls"); goto start_sort; }
			if (inp == 0) { system("cls"); goto start; }
		}
	}
	return 0;
}