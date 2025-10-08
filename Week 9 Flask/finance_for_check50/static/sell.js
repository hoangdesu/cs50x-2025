const sellTotal = document.querySelector('#sell-total');
const price = document.querySelector('input[name="price"]');
const shares = document.querySelector('input[name="shares"]');

shares.addEventListener('input', evt => {
    sellTotal.textContent = `Total: $${(parseInt(shares.value || 0) * parseFloat(price.value) || 0).toFixed(2)}`;
});

