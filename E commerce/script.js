let cart = JSON.parse(localStorage.getItem("cart")) || [];
updateCartUI();

function addToCart(price, name) {
    cart.push({ name, price });
    localStorage.setItem("cart", JSON.stringify(cart));
    updateCartUI();
    alert(`${name} added to cart!`);
}

function removeFromCart(index) {
    cart.splice(index, 1);
    localStorage.setItem("cart", JSON.stringify(cart));
    updateCartUI();
}

function updateCartUI() {
    let cartList = document.getElementById("cart-items");
    let cartCount = document.getElementById("cart-count");
    let totalPrice = document.getElementById("total-price");

    if (cartList) {
        cartList.innerHTML = "";
        let total = 0;

        cart.forEach((item, index) => {
            let listItem = document.createElement("li");
            listItem.innerHTML = `${item.name} - $${item.price} 
            <button onclick="removeFromCart(${index})">Remove</button>`;
            cartList.appendChild(listItem);
            total += item.price;
        });

        totalPrice.innerText = total;
    }

    if (cartCount) {
        cartCount.innerText = cart.length;
    }
}

function placeOrder() {
    alert("Order Placed Successfully!");
    localStorage.removeItem("cart");
    updateCartUI();
    window.location.href = "index.html";
}
