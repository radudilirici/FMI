var colors = ["white", "#81bde8", "#4fa2dd", "#2692e0", "#0375c6", "#024c82", "#023559"];
var currColor = 0;
var currIcons = 0;
var maxIcons = 6;
var iframeNo = 0;

stop = function(event) {
    event.stopPropagation();
};

changeBackgroundColorRandomly = function (element, brightness) {
    let caractere = "0123456789abcdef";
    let culoare = '#';
    for (let i = 0; i < 3; i++) {
        culoare += caractere[Math.floor(Math.random() * 3 + brightness)];
        culoare += caractere[Math.floor(Math.random() * 16)];
    }
    element.style.backgroundColor = culoare;
};

addOnClickImageReplace = function (item, index) {
    item.onclick = function () {
        let sImage = document.getElementsByClassName("selected-image")[0].children[0];
        let sImageImg = sImage.querySelector("img");
        let sImageFigc = sImage.querySelector("figcaption");

        let kidImage = item.children[0].children[0];
        let kidFigc = item.children[0].children[1];

        sImageImg.setAttribute("src", kidImage.src);
        sImageFigc.innerHTML = kidFigc.innerHTML;

        localStorage.setItem("img-src", kidImage.src);
        localStorage.setItem("fig-inner", kidFigc.innerHTML);
    }
};

window.addEventListener("load", function () {

    let gt = document.getElementById("gallery-table");
    let rows = gt.rows;
    for (let i = 0; i < rows.length; i++) {
        let cells = Array.from(rows[i].cells);
        cells.forEach(addOnClickImageReplace);
    }

    let sImage = document.getElementsByClassName("selected-image")[0].children[0];
    let imgsrc = localStorage.getItem("img-src");
    let figinner = localStorage.getItem("fig-inner");
    if (imgsrc != null && figinner != null) {
        let sImageImg = sImage.querySelector("img");
        let sImageFigc = sImage.querySelector("figcaption");
        sImageImg.setAttribute("src", imgsrc);
        sImageFigc.innerHTML = figinner;
    }
    sImage.onclick = function () {
        if (sImage.classList.length > 0) {
            return;
        }
        sImage.classList.add("rotationClass");

        if (iframeNo == 0) {
            let ifrm = document.createElement("iframe");
            ifrm.src = "https://en.wikipedia.org/wiki/Hellblade:_Senua's_Sacrifice";
            ifrm.className = "wiki-iframe";
            document.body.appendChild(ifrm);
            iframeNo++;
        }

        setTimeout(function () {
            sImage.classList.remove("rotationClass");
        }, 2000);
    };

    let headerText = document.querySelector(".add-image-button");
    headerText.onclick = function() {
        if (currIcons < maxIcons) {
            let header = this.parentElement;
            currColor++;
            if (currColor == colors.length) {
                currColor--;
            }
            headerText.style.color = colors[currColor];
            let icon = document.createElement("img");
            icon.src = "../media/senua-icon.png";
            icon.style.height = "2em";
            icon.style.padding = "auto 10px";
            icon.onclick = function () {
                icon.remove();
                currIcons--;
                currColor--;
                if (currColor == -1) {
                    currColor = 0;
                }
                headerText.style.color = colors[currColor];
            };
            header.appendChild(icon);
            currIcons++;
        }
    };


    let bdy = document.querySelector("body");
    bdy.onkeydown = function (e) {
        let wrp = document.querySelector(".wrapper");
        let pdg = parseInt(getComputedStyle(wrp).paddingLeft);
        let wdth = parseInt(getComputedStyle(wrp).width);
        if (e.key == 'ArrowRight') {
            if (wdth - pdg >= 410) {
                wrp.style.paddingLeft = pdg + 10 + "px";
            }
        }
        else if (e.key == 'ArrowLeft') {
            if (pdg >= 10) {
                wrp.style.paddingLeft = pdg - 10 + "px";
            }
        }
    };
    bdy.addEventListener("click", function () {
        bdy.style.backgroundImage = 'url("../media/hellblade_background.jpg")';
    }, true);

    let nav = document.querySelector(".nav-header");
    let colorChange = setInterval(changeBackgroundColorRandomly, 2000, nav, 2);
    let dropdown = document.querySelector(".dropdown");
    dropdown.addEventListener("click", stop);
    nav.onclick = function () {
        clearInterval(colorChange);
    }

});