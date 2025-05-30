# Стили текста

Для разметки стилей текста используется собственный диалект Markdown.
Форматирование работает на UI элементах: label и textbox, если явно указано `markup="md"`.

## Стили

| Стиль        | Пример                    | Вывод                         |
| ------------ | ------------------------- | ----------------------------- |
| Жирный       | `**Жирный шрифт**`        | **Жирный шрифт**              |
| Курсив       | `*Текст курсивом*`        | *Текст курсивом*              |
| Подчеркнутый | `__Подчеркнутый текст__`  | <ins>Подчеркнутый текст</ins> |
| Зачеркнутый  | `~~Зачеркнутый текст~~`   | ~~Зачеркнутый текст~~         |

Стили могут объединяться. Пример:
```md
***__Сообщение__***, демонстрирующее *~~обедненные~~ объединенные* стили__~~.~~__
```
Вывод:

***<ins>Сообщение</ins>***, демонстрирующее *~~обедненные~~ объединенные* стили<ins>~~.~~</ins>

## Цвета

Цвет текста задается при помощи цветового кода: [#RRGGBB]

| Компонент        | Назначение                    |
| ------------ | ------------------------- |
| R       | Используется для интенсивности красного        |
| G       | Используется для интенсивности зеленого        |
| B       | Используется для интенсивности синего        |

### Например:

<span style="color: #ff0000">
    <span style="color:rgb(105, 105, 105)">
    [#ff0000]
    </span>Красный Текст
</span>

<span style="color: #00ff00">
    <span style="color:rgb(105, 105, 105)">
    [#00ff00]
    </span>Зеленый Текст
</span>

<span style="color: #0000ff">
    <span style="color:rgb(105, 105, 105)">
    [#0000ff]
    </span>Синий Текст
</span>