var d1 = document.getElementById("div1");
var c_link = document.getElementById("c_link");
c_link.onclick = function() {
 d1.innerHTML = "<strong>Right now!</strong> Was that quick or what?";
 return false;
};