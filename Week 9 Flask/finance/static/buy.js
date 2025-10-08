const buyTotal = document.querySelector('#buy-total');
const price = document.querySelector('input[name="price"]');
const shares = document.querySelector('input[name="shares"]');

shares.addEventListener('input', evt => {
    buyTotal.textContent = `Total: $${(parseInt(shares.value || 0) * parseFloat(price.value) || 0).toFixed(2)}`;
});

