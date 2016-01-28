# Domain Black List

Este módulo te permite añadir dominios en una lista negra para que no
aparezcan en tu sitio.

Hay tres tipos de baneo y cada uno de ellos se puede activar o desactivar en el
formulario de configuración admin/config/system/domain-black-list/manage/settings
donde también puedes activar un modo debug que te mostrará un mensaje con los
resultados obtenidos.

- Eliminar los dominios de la salida HTML: una vez drupal renderiza la salida
HTML, se ejecuta un filtrado que elimina todos los enlaces <a> que contengan en
su atributo HTML href uno de los dominios de la lista.

- Eliminar los links de la función url(): todas las rutas que pasan por la función
url() y contienen uno de los dominios de la lista negra son cambiadas y apuntarán
a la página de inicio del site.

- Añadir validaciones de los fields: esta característica activa una validación en
todas las entidades para evitar que se introduzcan los dominios de la lista negra
en los campos que estén configurados para ello.

Se pueden añadir, editar, eliminar, activar y desactivar dominios a través de la
página principal del módulo admin/config/system/domain-black-list/manage
donde también encontramos un listado de todos ellos.

Hay tres pestañas de ejemplo que te permiten ver mejor el funcionamiento de cada
apartado, para ello es recomendable activar la opción de debur y probar activando
y desactivando cada opción en cada ejemplo.

A lo largo del módulo hay @todos con mejoras y propuestas, también decir que hay
algunos aspectos mejorables como las expresiones regulares utilizadas.

@todo English version