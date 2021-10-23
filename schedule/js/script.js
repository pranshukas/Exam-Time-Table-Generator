const form = document.getElementById("form");
const input = document.getElementById("input");
const data = document.querySelector(".data");

form.addEventListener("submit", (e) => {
    e.preventDefault();
    if (+input.value >= 4) {
        input.value = "";
        alert("Currently Not Supporting More than 3 Semesters");
        refresh();
    } else if (+input.value <= 0) {
        input.value = "";   
        alert("Please Enter Valid Input");
        refresh();
    } else {
        data.style.display = "none";
        createSemesters(input.value);
    }
});

function createSemesters(numberofSemesters) {
    const createSemesters = document.querySelector(".create-semesters");
    createSemesters.style.display = "flex";
    
    const addButtons = document.querySelectorAll(".btn-add");
    addButtons.forEach((button) => {
        button.addEventListener("click", () => {
            // console.log(button.parentNode.querySelector(".card"));
            const card = button.parentNode.querySelector(".card");
            const inp = document.createElement('input');
            card.appendChild(inp);
        });
    });

    const subButtons = document.querySelectorAll(".btn-sub");
    subButtons.forEach((button) => {
        button.addEventListener("click", () => {
            // console.log(button.parentNode.querySelector(".card"));
            const card = button.parentNode.querySelector(".card");
            card.removeChild(card.lastChild);
        });
    });
}
