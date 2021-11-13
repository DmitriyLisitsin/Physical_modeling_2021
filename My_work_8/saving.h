#ifndef saving_h
#define saving_h

#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

template<typename type>
void save_data(std::string path, std::vector<type> const &T,
               std::vector<std::vector<type>> const &P, std::vector<type> const &params, int n)
    {
        std::ofstream out;
        out.open(path);
        if (out.is_open()){
            out << std::setprecision(8);
            out << std::scientific;
            for(int i = 0; i<params.size()-1; ++i){
                out << params[i] << ' ';
            }
            out << params[params.size()-1] << '\n';
            for(int i = 0; i<T.size(); ++i){
                out << T[i];
                for(int j=0; j<n; ++j){
                    out << ' ' << P[i][j] << ' ';
                }
                out << '\n';
            }
        }
        out.close();
    }

int CountLinesInFile(std::string filename)
{
  std::ifstream F(filename, std::ios::in);
  if (!F) {
    return -1;
  }
  int count = 0;
  char buffer[1000];
  while (!F.eof()){
    ++count;
    F.getline(buffer, 1000);
  }
  F.close();
  return count;
}

int GetStringsFromFileC(std::string filename, char*** _lines = nullptr)
{
  // 1. �������������� ����������
  char** lines;
  int n = CountLinesInFile(filename); // �������� ���������� ����� � �����

  // 2. ��������, �������� �� ���������� �����
  if (n == -1) return -1;

  // 3. �������� �������� ����������
  std::ifstream F(filename); // ������� ���� ��� ������

  // 4. ��������, �������� �� ����
  if (!F) return -1;

  // 5. ������� �������� ������ ��� n �����
  try
  {
    lines = new char* [n];
  }
  catch (std::bad_alloc e)
  {
    // ���� ���������� �������� ������, �� �����
    std::cout << e.what() << std::endl; // ������� ��������� �� ������
    F.close(); // ������� ����
    return -1;
  }

  // 6. ���� ������ ����� � ��������� ������ ��� ���
  int len; // ����� ����� ������
  char buffer[1000]; // ������, ���� ������������ ���� ������ �� �����

  for (int i = 0; i < n; i++)
  {
    // 6.1. ������� ������ �� �����
    F.getline(buffer, 1000);

    // 6.2. ���������� ����� ����������� ������
    for (len = 0; buffer[len] != '\0'; len++);

    // 6.3. �������� ������ ��� len+1 ��������
    lines[i] = new char[len + 1];

    // 6.4. ����������� ������ �� buffer � lines[i]
    for (int j = 0; j < len; j++)
      lines[i][j] = buffer[j];
    lines[i][len] = '\0'; // �������� ������ ����� ������
  }

  // 7. ������� ����
  F.close();

  // 8. �������� ���������
  *_lines = lines;
  return n;
}

bool ChangeStringInFileC(std::string filename, int position, std::string str)
{
  // 1. �������� ������ ����� � ���� ������
  char** lines; // ������ ����� �����
  int count; // ���������� ����� �����
  count = GetStringsFromFileC(filename, &lines); // �������� ������ lines

  // 2. ��������, ��������� �� �������� ����
  if (count < 0) return false;

  // 3. ��������, ��������� �� ������� 0 <= position < count
  if ((position < 0) || (position >= count)) return false;

  // 4. ������ ����� lines � ���� �� ������� position
  std::ofstream F(filename); // ������� ���� ��� ������

  // 5. ��������, �������� �� ���� ��������� - ������� is_open()
  if (!F.is_open()) return false;

  if (position < count-1){
      for (int i = 0; i < position; i++)
        F << lines[i] << std::endl; // ������� ������ � ����

      // 6. ������ ������ � ������� position
      F << str.c_str() << std::endl; // ����� ������� ������ str

      // 7. ������ ����� ����� ������� position
      for (int i = position + 1; i < count - 1; i++)
        F << lines[i] << std::endl;

      // 8. �������� ��������� ������ ��� ������� '\n'
      F << lines[count - 1];
  }
  else{
      for (int i = 0; i < count - 1; i++)
        F << lines[i] << std::endl;

      // 8. �������� ��������� ������ ��� ������� '\n'
      F << str.c_str();
  }

  // 9. ������� ����
  F.close();

  // 10. ���������� ������, ���������� ��� �����
  for (int i = 0; i < count; i++)
    delete lines[i];

  // 11. ���������� ��������� �� ������
  delete[] lines;
  return true;
}

#endif // saving_h
