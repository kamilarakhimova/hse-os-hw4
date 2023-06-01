# hse-os-hw4
---
# ИДЗ №4 по предмету "Операционнные системы"

# Курс 2, ПИ, ФКН, НИУ ВШЭ

# Вариант 14, Рахимова Камила Мухаммадовна, БПИ214

---

## *Тема:* 

#### *Сетевые взаимодействия с применением транспортного протокола UDP*

---

## *Условие задачи:*

Задача о гостинице – 3 (дамы и джентльмены). В гостинице 10 номеров рассчитаны на одного человека и 15 номеров рассчитаны на двух человек. В гостиницу случайно приходят клиенты–дамы и клиенты–джентльмены, и конечно они могут провести ночь в номере только с представителем своего пола. Если для клиента не находится подходящего номера, он уходит искать ночлег в другое место. Клиенты порождаются динамически и уничтожаются при освобождении номера или уходе из гостиницы при невозможности поселиться. Создать приложение, моделирующее работу гостиницы.

Гостиница — сервер. Каждого гостя реализовать в виде отдельного клиента, порождаемого вручную.

---

## *Сценарий решаемой задачи:*

Собственно сценарий уже описан в условии. Гостиница является сервером, а клиенты -- клиентами. Так как условие может быть интерпретировано на собственное усмотрение, для упрощения я решила работать только с n клиентами (количество n задаётся в программе "server.c"), создаваемыми вручную.

Администратор (сервер) после запуска ожидает клиентов.
Клиенты подключаются поочередно, передают данные о своём поле (женский/мужской) и о виде желаемого номера (одноместный/двухместный).
Администратор (сервер) получает данные от клиента и обрабатывает запрос. Далее рандомно берет ключ от номера желаемого вида. И, если клиент подходит под условия для проживания в этой комнате, заселяет его. Иначе сообщает по какой причине не может заселить клиента.

---

## *Примечания:*

✔️ Программа с момента запуска и до завершения работы моделирует одну ночь работы отеля. Соответственно клиенты уничтожаются с рассветом (по окончании работы программы).

✔️ В данном варианте нет необходимости в наборе тестовых файлов для понимания работы программы. Результатом моделирования работы гостиницы является описание результатов действий сервера, выводимое программой.

✔️ Каждая программа запускается в отдельном терминале (кроме, может, клиентов-гостей "client.c", их можно запускать поочерёдно в одном терминале). Для корректной отработки системы необходимо лишь указать используемый порт для сервера (рекомендуется использовать пользовательские порты с номерами 1024—49151). IP-адрес для сервера программа "server.c" самостоятельно выводит в самом начале работы. Именно эти IP-адрес и порт вводятся в качестве аргументов при запуске остальных программ.

---

## *Отчёт*

Работа выполнена с расчётом на получение оценки в 10/10 баллов.

### ◉ Требования на 4-5 баллов:

Сами программы расположились [здесь](https://github.com/kamilarakhimova/hse-os-hw4/tree/main/4-5%20баллов).

### *Задача:*

Разработать клиент–серверное приложение, в котором сервер и клиенты независимо друг от друга отображают только ту информацию, которая поступает им во время обмена. То есть, отсутствует какой-либо общий вывод интегрированной информации, отображающий поведение системы в целом.

#### *Примечания:*

Количество клиентов-гостей, желающих заселиться в отель задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу клиента столько раз, сколько у нас клиентов (в моём примере их 2):
```
~/os-mini-hw1$ gcc -o client client.c
~/os-mini-hw1$ ./client <server_ip_address> <server_port>
```


✔ Результат выполнения программы сервера:

```
server ip address = <server_ip_address>
Добро пожаловать на ночную экскурсию в отель.
Вы задали количество клиентов, ожидающих заселения, равным: 2.
Администратор (сервер) готов заселять клиентов.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 6.
Клиентка-дама заселилась первой в двухместный номер 6.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 8.
Клиентка-дама заселилась в одноместный номер 8.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в двухместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

---

### ◉ Требования на 6-7 баллов:

Сами программы расположились [тут](https://github.com/kamilarakhimova/hse-os-hw4/tree/main/6-7%20баллов).

### *Задача:*

В дополнение к программе на предыдущую оценку необходимо разработать клиентскую программу, подключаемую к серверу, которая предназначена для отображение комплексной информации о выполнении приложения в целом. То есть, данный программный модуль должен адекватно отображать поведение моделируемой системы, позволяя не пользоваться отдельными видами, предоставляемыми клиентами и серверами по отдельности.

#### *Примечания:*

Количество клиентов-гостей, желающих заселиться в отель всё также задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

Количество клиентов-наблюдателей определяется переменной "MAX_OBSERVERS" в программе "server.c". В требованиях на данную оценку оно обязательно равно 1.

```
#define MAX_OBSERVERS 1
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу наблюдателя:

```
~/os-mini-hw1$ gcc -o observer observer.c
~/os-mini-hw1$ ./observer <server_ip_address> <server_port>
```

✔ Запускаем работу клиента столько раз, сколько у нас клиентов (в моём примере их 2):
```
~/os-mini-hw1$ gcc -o client client.c
~/os-mini-hw1$ ./client <server_ip_address> <server_port>
```

✔ Результат выполнения программы сервера:

```
server ip address = <server_ip_address>
Добро пожаловать на ночную экскурсию в отель.
Вы задали количество клиентов, ожидающих заселения, равным: 2.
Вы задали количество наблюдателей равным: 1.
Администратор (сервер) готов заселять клиентов.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя (1):

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

---

### ◉ Требования на 8 баллов:

Сами программы расположились [здесь](https://github.com/kamilarakhimova/hse-os-hw4/tree/main/8%20баллов).

### *Задача:*

В дополнение к предыдущей программе реализовать возможность, подключения множества клиентов, обеспечивающих отображение информации о работе приложения. Это должно позволить осуществлять наблюдение за поведением программы с многих независимых компьютеров.

#### *Примечания:*

Программы в требованиях на 8 баллов не сильно отличаются от программ в требованиях на 6-7 баллов. Важные изменения произошли лишь в программе "server.c".

Количество клиентов-гостей, желающих заселиться в отель всё также задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

Количество клиентов-наблюдателей всё также определяется переменной "MAX_OBSERVERS" в программе "server.c":

```
#define MAX_OBSERVERS 2
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу наблюдателя столько раз, сколько у нас наблюдателей (в моём примере их 2):

```
~/os-mini-hw1$ gcc -o observer observer.c
~/os-mini-hw1$ ./observer <server_ip_address> <server_port>
```

✔ Запускаем работу клиента столько раз, сколько у нас клиентов (в моём примере их 2):
```
~/os-mini-hw1$ gcc -o client client.c
~/os-mini-hw1$ ./client <server_ip_address> <server_port>
```

✔ Результат выполнения программы сервера:

```
server ip address = <server_ip_address>
Добро пожаловать на ночную экскурсию в отель.
Вы задали количество клиентов, ожидающих заселения, равным: 2.
Вы задали количество наблюдателей равным: 2.
Администратор (сервер) готов заселять клиентов.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 1.
Клиент-джентльмен заселился в одноместный номер 1.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 8.
Клиентка-дама заселилась в одноместный номер 8.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя 1:

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 1.
Клиент-джентльмен заселился в одноместный номер 1.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 8.
Клиентка-дама заселилась в одноместный номер 8.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя 2:

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 1.
Клиент-джентльмен заселился в одноместный номер 1.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 8.
Клиентка-дама заселилась в одноместный номер 8.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

---

### ◉ Требования на 9-10 баллов:

Сами программы расположились [здесь](https://github.com/kamilarakhimova/hse-os-hw3/tree/main/9-10%20баллов).

### *Задача:*

В дополнение к программам на предыдущие оценки необходимо разработать приложение, позволяющее отключать и подключать различных клиентов с сохранением работоспособности сервера.

Расширить программу таким образом, чтобы при завершении работы сервера происходило корректное завершение работы всех подключенных клиентов.


#### *Примечания:*

Клиенты-наблюдатели могут успешно отключаться и подключаться снова с помощью использования сигналов.

При завершении работы сервера происходит корректное завершение работы всех подключенных клиентов (выполнялось и в программах на более низкую оценку):

```
for (i = 0; i < MAX_CLIENTS; ++i) {
    close(client_sockets[i]);
}
for (i = 0; i < MAX_OBSERVERS; ++i) {
    close(observer_sockets[i]);
}
close(server_sockfd);
```

Количество клиентов-гостей, желающих заселиться в отель всё также задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

Количество клиентов-наблюдателей всё также определяется переменной "MAX_OBSERVERS" в программе "server.c":

```
#define MAX_OBSERVERS 2
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу наблюдателя столько раз, сколько у нас наблюдателей (в моём примере их 2):

```
~/os-mini-hw1$ gcc -o observer observer.c
~/os-mini-hw1$ ./observer <server_ip_address> <server_port>
```

✔ Запускаем работу клиента столько раз, сколько у нас клиентов (в моём примере их 2):
```
~/os-mini-hw1$ gcc -o client client.c
~/os-mini-hw1$ ./client <server_ip_address> <server_port>
```

✔ Результат выполнения программы сервера:

```
server ip address = <server_ip_address>
Добро пожаловать на ночную экскурсию в отель.
Вы задали количество клиентов, ожидающих заселения, равным: 2.
Вы задали количество наблюдателей равным: 2.
Администратор (сервер) готов заселять клиентов.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиентка-дама заселилась первой в двухместный номер 5.
Ищем покинувшего нас наблюдателя
Ой, наблюдатель 1 покинул нас( Ну ничего, посидим, подождём его...
Порядок, наблюдатель 1 вернулся в строй.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 12.
Клиент-джентльмен заселился первым в двухместный номер 12.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя 1:

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 1.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиентка-дама заселилась первой в двухместный номер 5.
^C
Успешно установлено подключение наблюдателя к серверу.
^C
```

✔ Результат выполнения программы наблюдателя 2:

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 2.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиентка-дама заселилась первой в двухместный номер 5.
Ищем покинувшего нас наблюдателя
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 12.
Клиент-джентльмен заселился первым в двухместный номер 12.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в двухместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в двухместный номер.
Клиент отошёл от стойки регистрации.
```

