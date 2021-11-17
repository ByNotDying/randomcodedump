window.alert(div1.title);

var new_div = document.createElement("div");
new_div.appendChild(document.createTextNode("See you!"));
new_div.setAttribute("title", "Lucky!");

div1.appendChild(new_div);