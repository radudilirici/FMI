var colors = ["white", "#81bde8", "#4fa2dd", "#2692e0", "#0375c6", "#024c82", "#023559"]
var currColor = 0
var currIcons = 0
var maxIcons = 6
var iframeNo = 0

removeRotationClass = function () {
    let sImages = document.getElementsByClassName("selected-image")
    let sImage = sImages[0].children[0]
    sImage.classList.remove("rotationClass")
}

window.addEventListener("load", function () {
    let gt = document.getElementById("gallery-table")
    let rows = gt.rows
    let sImages = document.getElementsByClassName("selected-image")
    let sImage = sImages[0].children[0]
    let sImageImg = sImage.children[0]
    let sImageFigc = sImage.children[1]
    for (let i = 0; i < rows.length; i++) {
        for (let td of rows[i].cells) {
            td.onclick = function () {
                let kidImage = td.children[0].children[0]
                let kidFigc = td.children[0].children[1]
                sImageImg.setAttribute("src", kidImage.src)
                sImageFigc.innerHTML = kidFigc.innerHTML
            }
        }
    }
    sImage.onclick = function () {
        if (sImage.classList.length > 0) {
            return
        }
        sImage.classList.add("rotationClass")

        if (iframeNo == 0) {
            var ifrm = document.createElement("iframe")
            ifrm.src = "https://en.wikipedia.org/wiki/Hellblade:_Senua's_Sacrifice"
            ifrm.style.width = "100%"
            ifrm.style.height = "600px"
            document.body.appendChild(ifrm)
            iframeNo++
        }

        setTimeout(removeRotationClass, 2000);
    }
    let header = document.querySelector(".page-header")
    let headerText = header.children[0]
    headerText.onclick = function() {
        if (currIcons < maxIcons) {
            currColor++
            if (currColor == colors.length) {
                currColor--
            }
            headerText.style.color = colors[currColor]
            var icon = document.createElement("img")
            icon.src = "../media/senua-icon.png"
            icon.style.height = "2em"
            icon.style.margin = "auto 10px"
            icon.onclick = function () {
                icon.remove()
                currIcons--
                currColor--
                if (currColor == -1) {
                    currColor = 0
                }
                headerText.style.color = colors[currColor]
            }
            header.appendChild(icon)
            currIcons++
        }
    }
})