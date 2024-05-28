# PasswordGenerator

![image](https://github.com/tailogs/GeneratePassword/assets/69743960/087e8404-046f-41c3-a09d-8b7c7f5a6bbf)

*Рисунок 1. Интерфейс приложения Password Generator*

---

## Описание

Простой генератор паролей для Windows с графическим интерфейсом. Позволяет генерировать пароли с различными настройками и копировать их в буфер обмена.

---

## Возможности

- Генерация паролей с использованием строчных букв, прописных букв, цифр и специальных символов.
- Настройка длины пароля.
- Копирование сгенерированного пароля в буфер обмена.
- Темная тема интерфейса.

---

## Установка и запуск

### Предварительные требования

- Компилятор GCC для Windows (например, MinGW).
- Средства сборки Make.

### Компиляция и запуск из исходных кодов

1. Склонируйте проект:

    ```sh
    git clone https://github.com/tailogs/PasswordGenerator.git
    ```
    
    ```sh
    cd PasswordGenerator
    ```

2. Скомпилируйте приложение с помощью Make:

    ```sh
    make
    ```

    Если у вас уже существует скомпилированный бинарный файл `PasswordGenerator.exe`, используйте команду `make clean` перед компиляцией для удаления старого бинарного файла.

3. Запустите приложение:

    ```sh
    make run
    ```

4. После завершения работы удалите скомпилированные файлы:

    ```sh
    make clean
    ```

### Использование

1. Откройте приложение Password Generator.
2. Настройте параметры генерации пароля, отметив необходимые опции (строчные буквы, прописные буквы, цифры, символы).
3. Укажите желаемую длину пароля в соответствующем поле.
4. Нажмите кнопку "Сгенерировать", чтобы получить пароль.
5. Чтобы скопировать пароль в буфер обмена, нажмите кнопку "Скопировать".

---

## Примечания

- Убедитесь, что файл `main.c` сохранен в кодировке Windows 1251, чтобы избежать проблем с кодировкой в строках сообщений.

---

## Лицензия

Проект распространяется по лицензии MIT. См. файл `LICENSE` для подробностей.