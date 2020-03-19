window.addEventListener("load", function () {
    let topButton = document.querySelector(".top-button");
    topButton.onclick = function () {
        document.documentElement.scrollTop = 0;
    }
});