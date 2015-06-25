<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>AboutDialog</name>
    <message>
        <location filename="../aboutdialog.ui" line="14"/>
        <source>About Password Manager</source>
        <translation>О Программе</translation>
    </message>
    <message>
        <location filename="../aboutdialog.ui" line="51"/>
        <source>Password Manager</source>
        <translation>Менеджер паролей</translation>
    </message>
    <message>
        <location filename="../aboutdialog.ui" line="61"/>
        <source>Powered by: Qt 5.4</source>
        <translation>Используются технологии: Qt 5.4</translation>
    </message>
    <message>
        <location filename="../aboutdialog.ui" line="68"/>
        <source>Licensed by: GPLv3</source>
        <translation>Лицензия: GPLv3</translation>
    </message>
    <message>
        <location filename="../aboutdialog.ui" line="75"/>
        <source>Created by: Chagochkin M.</source>
        <translation>Разработал: Чагочкин М.В.</translation>
    </message>
    <message>
        <location filename="../aboutdialog.ui" line="95"/>
        <source>Source code: &lt;a href=&quot;https://github.com/Avengerrr/Pass_Manager&quot;&gt;GitHub&lt;/a&gt;</source>
        <translation>Исходный код: &lt;a href=&quot;https://github.com/Avengerrr/Pass_Manager&quot;&gt;GitHub&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>HelpDialog</name>
    <message>
        <location filename="../helpdialog.ui" line="20"/>
        <source>Password Manager Help</source>
        <translation>Справка</translation>
    </message>
    <message>
        <location filename="../helpdialog.ui" line="64"/>
        <source>&lt;!DOCTYPE html&gt; 
&lt;html&gt;
&lt;head&gt;
	&lt;meta charset=&apos;utf-8&apos;&gt;
	&lt;title&gt;Help&lt;/title&gt;
	&lt;style&gt;
   		li { list-style-type: none; } /* Убираем исходную нумерацию у списка */
   		ol { counter-reset: list1; } /* Инициируем счетчик */
   		ol li:before {
	    	counter-increment: list1; /* Увеличиваем значение счетчика */
	    	content: counter(list1) &quot;. &quot;; /* Выводим число */
   		}
   		ol ol { counter-reset: list2; } /* Инициируем счетчик вложенного списка */
   		ol ol li:before {
	    	counter-increment: list2; /* Увеличиваем значение счетчика вложенного списка */
	    	content: counter(list1) &quot;.&quot; counter(list2) &quot;. &quot;; /* Выводим число */
   		}
   		.numeric { counter-reset: listh1; } /* Инициируем счетчик */
   		.numeric h3:before {
	    	counter-increment: listh1; /* Увеличиваем значение счетчика */
	    	content: counter(listh1) &quot;. &quot;; /* Выводим число */
   		}
   		.numeric .numeric2 { counter-reset: listh2; } /* Инициируем счетчик вложенного списка */
   		.numeric .numeric2 h4:before {
	    	counter-increment: listh2; /* Увеличиваем значение счетчика вложенного списка */
	    	content: counter(listh1) &quot;.&quot; counter(listh2) &quot;. &quot;; /* Выводим число */
   		}
  &lt;/style&gt;
&lt;/head&gt;
&lt;body background=&quot;img/Paper.jpg&quot; font=&quot;Georgia&quot;&gt;
	&lt;h3&gt;Справочник пользователя&lt;/h3&gt;
		&lt;hr&gt;
		&lt;h3&gt;Содержание:&lt;/h3&gt;
		&lt;ol&gt;
	  		&lt;li&gt;Интерфейс приложения&lt;/li&gt;
	  		&lt;ol&gt;
	    		&lt;li&gt;Главное окно&lt;/li&gt;
	    		&lt;li&gt;Окно просмотра записей&lt;/li&gt;
	    		&lt;li&gt;Окно добавления записи&lt;/li&gt;
	    		&lt;li&gt;Окно блокировки&lt;/li&gt;
	  		&lt;/ol&gt;
	  		&lt;li&gt;Дополнительная информация&lt;/li&gt;
	  		&lt;ol&gt;
	    		&lt;li&gt;Горячие клавиши&lt;/li&gt;
	    		&lt;li&gt;Служба поддержки&lt;/li&gt;
	    		&lt;li&gt;Исходный код&lt;/li&gt;
	  		&lt;/ol&gt;
		&lt;/ol&gt;

		&lt;hr&gt;
		&lt;div class=&quot;numeric&quot;&gt;
			&lt;h3 align=&quot;center&quot;&gt;Интерфейс приложения&lt;/h3&gt;
			&lt;div class=&quot;numeric2&quot;&gt;
				&lt;h4&gt;Главное окно&lt;/h4&gt;
				
				&lt;p&gt;Разработка оптимального интерфейса программного продукта была реализована благодаря следованию 	следующих принципов построения интерфейса для пользователя:&lt;/p&gt;
				&lt;p&gt;- интерфейс должен быть интуитивно понятным. Таким, чтобы пользователю не требовалось объяснять как им пользоваться;&lt;/p&gt;
				&lt;p&gt;- для упрощения процесса изучения необходима справка. Буквально – графическая подсказка, объясняющая значение того или иного элемента интерфейса. Полное руководство должно быть частью интерфейса, доступной в любой момент;&lt;/p&gt;
				&lt;p&gt;- возврат пользователя в то место, где им была закончена работа во-время прошлой сессии;&lt;/p&gt;
				&lt;p&gt;- чаще всего, пользователи в интерфейсе сначала ищут сущность(существительное), а затем действие(глагол) к ней;&lt;/p&gt;
				&lt;p&gt;- чем быстрее человек увидит результат – тем лучше. Пример – «живой» поиск, когда варианты, в процессе набора поискового запроса. Основной принцип: программа должна взаимодействовать с пользователем на основе наименьшей значимой единицы ввода.&lt;/p&gt;
				&lt;p&gt;Исходя из этих несложных принципов, был спроектирован интуитивно понятный интерфейс, в котором есть все необходимое для реализации поставленной цели дипломного проекта.&lt;/p&gt;
			&lt;/div&gt;

			&lt;div class=&quot;numeric2&quot;&gt;
				&lt;h4&gt;Окно просмотра записей&lt;/h4&gt;

				&lt;p&gt;При запуске программного продукта, пользователю предоставляется во внимание главное окно приложения, в котором содержится два элемента управления в виде клавиш, отвечающих за создание нового файла, либо открытие, ранее созданного.&lt;/p&gt;
				&lt;center&gt;&lt;img src=&quot;:/html/help/images/html/help/ru/mainwindow.jpg&quot;&gt;&lt;/center&gt;
			&lt;/div&gt;

		&lt;/div&gt;
&lt;/body&gt;
&lt;/html&gt;</source>
        <translation></translation>
    </message>
    <message>
        <source>Adding records</source>
        <translation type="vanished">Добавление записей</translation>
    </message>
    <message>
        <source>Deleting records</source>
        <translation type="vanished">Удаление записей</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <source>MainWindow</source>
        <translation type="vanished">Главное окно</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="14"/>
        <source>Password Manager</source>
        <translation>Менеджер паролей</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="74"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;img src=&quot;:/images/logotipmain.png&quot;/&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="93"/>
        <source>Creation of the new file</source>
        <translation>Создание нового файла</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="96"/>
        <source>New file</source>
        <translation>Новый файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="106"/>
        <source>Opening of earlier created file</source>
        <translation>Открытие ранее созданного файла</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="109"/>
        <source>Open file</source>
        <translation>Открыть файл</translation>
    </message>
    <message>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Используются технологии: Qt 5.4&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Разработал: Чагочкин М.В.&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Лицензия: GPLv3&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="vanished">&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Powered by: Qt 5.4&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Created by: Chagochkin M.V.&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Licensed by: GPLv3&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="116"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Powered by: Qt 5.4&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Created by: Chagochkin M.V.&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Licensed by: GPLv3&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Используются технологии: Qt 5.4&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Разработал: Чагочкин М.В.&lt;/span&gt;&lt;/p&gt;&lt;p align=&quot;center&quot;&gt;&lt;span style=&quot; font-style:italic; color:#474747;&quot;&gt;Лицензия: GPLv3&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="223"/>
        <location filename="../mainwindow.ui" line="451"/>
        <source>File of database</source>
        <translation>Файл базы данных</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="236"/>
        <location filename="../mainwindow.ui" line="464"/>
        <source>Specify a directory</source>
        <translation>Укажите дерикторию</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="239"/>
        <location filename="../mainwindow.ui" line="467"/>
        <source>...</source>
        <translation>...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="264"/>
        <location filename="../mainwindow.ui" line="489"/>
        <location filename="../mainwindow.ui" line="845"/>
        <location filename="../mainwindow.ui" line="854"/>
        <location filename="../mainwindow.ui" line="994"/>
        <location filename="../mainwindow.cpp" line="414"/>
        <source>Password</source>
        <translation>Пароль</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="274"/>
        <location filename="../mainwindow.ui" line="499"/>
        <location filename="../mainwindow.ui" line="1280"/>
        <source>Show/Hide</source>
        <translation>Показать/Скрыть</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="296"/>
        <source>Full all fields</source>
        <translation>Заполните все поля</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="311"/>
        <source>Session timeout</source>
        <translation>Время сессии вышло</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="314"/>
        <source>Specify session time</source>
        <translation>Укажите время сессии</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="317"/>
        <location filename="../mainwindow.ui" line="546"/>
        <source> min</source>
        <translation> мин</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="352"/>
        <location filename="../mainwindow.ui" line="578"/>
        <location filename="../mainwindow.ui" line="1193"/>
        <source>&lt; Cancel</source>
        <translation>&lt; Отмена</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="365"/>
        <source>Open &gt;</source>
        <translation>Открыть &gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="524"/>
        <location filename="../mainwindow.ui" line="899"/>
        <location filename="../mainwindow.ui" line="911"/>
        <source>Confirm password</source>
        <translation>Подтвердите пароль</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="534"/>
        <source>Fill all fields</source>
        <translation>Заполните все поля</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="591"/>
        <source>Create &gt;</source>
        <translation>Создать &gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="678"/>
        <source>Search</source>
        <translation>Поиск</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="761"/>
        <location filename="../mainwindow.cpp" line="144"/>
        <source>Group:</source>
        <translation>Группа:</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="768"/>
        <location filename="../mainwindow.cpp" line="427"/>
        <source>Groups</source>
        <translation>Группы</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="783"/>
        <source>Main info</source>
        <translation>Главная информация</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="792"/>
        <location filename="../mainwindow.ui" line="801"/>
        <location filename="../mainwindow.cpp" line="411"/>
        <source>Title</source>
        <translation>Название</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="811"/>
        <location filename="../mainwindow.ui" line="817"/>
        <location filename="../mainwindow.cpp" line="412"/>
        <source>URL</source>
        <translation>URL</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="827"/>
        <location filename="../mainwindow.ui" line="833"/>
        <location filename="../mainwindow.cpp" line="413"/>
        <source>Login</source>
        <translation>Логин</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="867"/>
        <source>&lt;</source>
        <translation>&lt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="883"/>
        <source>Difficulties</source>
        <translation>Сложность</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="921"/>
        <location filename="../mainwindow.ui" line="930"/>
        <source>Answer for secret question</source>
        <translation>Ответ на секретный вопрос</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="940"/>
        <location filename="../mainwindow.ui" line="958"/>
        <source>Phone number</source>
        <translation>Номер телефона</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="943"/>
        <source>Line editfor input phone number</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="949"/>
        <source>+()--</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="977"/>
        <location filename="../mainwindow.ui" line="980"/>
        <source>Comment</source>
        <translation>Комментарий</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1000"/>
        <source>Use following  character groups:</source>
        <translation>Используемые группы символов:</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1009"/>
        <source>&amp;Upper letters</source>
        <translation>&amp;Алфавит верхнего регистра</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1022"/>
        <source>&amp;Minus</source>
        <translation>&amp;Минус</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1032"/>
        <source>&amp;Lower letters</source>
        <translation>&amp;Алфавит нижнего регистра</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1045"/>
        <source>&amp;Numbers</source>
        <translation>&amp;Цифры</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1058"/>
        <source>&amp;Special characters</source>
        <translation>&amp;Специальные символы</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1071"/>
        <source>&amp;Underline</source>
        <translation>&amp;Подчеркивающая линия</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1086"/>
        <source>Length:</source>
        <translation>Длина:</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1114"/>
        <source>Relevance</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1117"/>
        <source>dd.MM.yyyy H:mm</source>
        <translation>дд.ММ.гггг Ч:мм</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1130"/>
        <source>Generate</source>
        <translation>Сгенерировать</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1190"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1203"/>
        <source>Keep Record</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1206"/>
        <source>Save &gt;</source>
        <translation>Сохранить &gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1249"/>
        <source>Session is locked</source>
        <translation>Сессия заблокирована</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1261"/>
        <source>Enter the password</source>
        <translation>Введите пароль</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1315"/>
        <source>Unlock</source>
        <translation>Разблокировать</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1364"/>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1374"/>
        <source>Language</source>
        <translation>Язык</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1381"/>
        <location filename="../mainwindow.ui" line="1606"/>
        <source>Help</source>
        <translation>Помощь</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1388"/>
        <source>Edit</source>
        <translation>Редактировать</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1404"/>
        <source>Main toolbar</source>
        <translation>Панель инструментов</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1433"/>
        <source>New file...</source>
        <translation>Новый файл...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1436"/>
        <location filename="../mainwindow.cpp" line="912"/>
        <source>Create new file</source>
        <translation>Создать новый файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1439"/>
        <source>Ctrl+N</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1448"/>
        <source>Open file...</source>
        <translation>Открыть файл...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1451"/>
        <source>Open existing file</source>
        <translation>Открыть исполняющий файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1454"/>
        <source>Ctrl+O</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1463"/>
        <source>Save file...</source>
        <translation>Сохранить файл...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1466"/>
        <source>Save file</source>
        <translation>Сохранить файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1469"/>
        <source>Ctrl+S</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1478"/>
        <source>Add record...</source>
        <translation>Добавить запись...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1481"/>
        <source>New record</source>
        <translation>Новая запись</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1484"/>
        <source>Ctrl+Y</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1493"/>
        <source>Edit record...</source>
        <translation>Редактировать запись...</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1496"/>
        <source>Edit selected record</source>
        <translation>Редактировать выбранную запись</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1499"/>
        <source>Ctrl+E</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1508"/>
        <source>Delete record</source>
        <translation>Удалить запись</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1511"/>
        <source>Delete selected record</source>
        <translation>Удалить выбранную запись</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1514"/>
        <source>Ctrl+D</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1523"/>
        <location filename="../mainwindow.ui" line="1526"/>
        <source>Copy name in clipboard</source>
        <translation>Копировать логин в буффер обмена</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1529"/>
        <source>Ctrl+B</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1538"/>
        <location filename="../mainwindow.ui" line="1541"/>
        <source>Copy password in clipboard</source>
        <translation>Копировать пароль в буффер обмена</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1544"/>
        <source>Ctrl+C</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1553"/>
        <source>Lock</source>
        <translation>Блокировка</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1556"/>
        <source>Lock main window</source>
        <translation>Блокировка главного окна</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1559"/>
        <source>Ctrl+L</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1568"/>
        <source>Open recent</source>
        <translation>Открыть последний</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1578"/>
        <location filename="../mainwindow.cpp" line="613"/>
        <source>Exit</source>
        <translation>Выход</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1581"/>
        <source>Ctrl+Q</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1590"/>
        <source>CopyUrl</source>
        <translation>Открыть URL</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1593"/>
        <source>Copy URL to clipboard</source>
        <translation>Открыть URL</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1596"/>
        <source>Ctrl+U</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1609"/>
        <source>F1</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1619"/>
        <source>About</source>
        <translation>О программе</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1627"/>
        <source>English</source>
        <translation>Английский</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1635"/>
        <source>Russian</source>
        <translation>Русский</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="147"/>
        <source>Creation:</source>
        <translation>Дата создания:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="152"/>
        <source>Login:</source>
        <translation>Логин:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="155"/>
        <source>Expiration:</source>
        <translation>Истечение срока:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="160"/>
        <source>URL:</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="163"/>
        <source>Password:</source>
        <translation>Пароль:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="168"/>
        <source>Comment:</source>
        <translation>Комментарий:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="473"/>
        <source>Cannot open encrypted file</source>
        <translation>Нельзя открыть зашифрованный файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="494"/>
        <location filename="../mainwindow.cpp" line="757"/>
        <location filename="../mainwindow.cpp" line="811"/>
        <location filename="../mainwindow.cpp" line="1143"/>
        <location filename="../mainwindow.cpp" line="1166"/>
        <source>Record count: </source>
        <translation>Количество записей:</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="614"/>
        <source>Save changes?</source>
        <translation>Сохранить изменения?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="623"/>
        <source>Enter a new file path</source>
        <translation>Выберите путь для нового файла</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="628"/>
        <source>Paswords is not identical</source>
        <translation>Пароли не совпадают</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="634"/>
        <location filename="../mainwindow.cpp" line="658"/>
        <source>Empty password is not allowed</source>
        <translation>Нельзя оставлять поле пароля пустым</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="646"/>
        <location filename="../mainwindow.cpp" line="921"/>
        <source>Choose a file</source>
        <translation>Выберите файл</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="653"/>
        <source>Choosen file is not exists</source>
        <translation>Такого файла не существует</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="989"/>
        <source>Password is uncorrect</source>
        <translation>Неверный пароль</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../db/connectionmanager.cpp" line="22"/>
        <source>Critical</source>
        <translation>Ошибка</translation>
    </message>
    <message>
        <location filename="../db/connectionmanager.cpp" line="23"/>
        <source>Cannot avalible database driver</source>
        <translation>Недоступен драйвер базы данных</translation>
    </message>
</context>
</TS>
