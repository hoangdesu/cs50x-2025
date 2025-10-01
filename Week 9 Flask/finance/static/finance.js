console.log('hehe');

// Quote

// Search Autocomplete
const searchBox = document.getElementById('searchBox');
const autocompleteMenu = document.getElementById('autocompleteMenu');

let debounceTimeout;
let data;

searchBox.addEventListener('input', (evt) => {
  // Clear previous timeout
  const inputValue = evt.target.value;

  if (!inputValue) {
    bootstrap.Dropdown.getInstance(searchBox)?.hide();
    data = null;
    return;
  }

  if (debounceTimeout) {
    clearTimeout(debounceTimeout);
  }

  // Set new timeout
  debounceTimeout = setTimeout(async () => {
    const res = await fetch(`/search?symbol=${inputValue}`);
    data = await res.json();

    console.log(data);

    autocompleteMenu.innerHTML = '';

    if (data && data.length > 0) {
      // reset autocompleteMenu

      // Show the dropdown
      for (const row of data) {
        const item = document.createElement('li');
        item.className = 'dropdown-item';
        item.textContent = `${row.symbol} - ${row.name}`;

        item.addEventListener('click', () => {
          searchBox.value = row.symbol;
        });

        autocompleteMenu.appendChild(item);
      }

      if (!bootstrap.Dropdown.getInstance(searchBox)) {
        new bootstrap.Dropdown(searchBox).show();
      } else {
        bootstrap.Dropdown.getInstance(searchBox).show();
      }
    } else if (inputValue) {
      const item = document.createElement('li');
      item.className = 'dropdown-item disabled';
      item.textContent = 'No matches found';
      autocompleteMenu.appendChild(item);
    }
  }, 500);
});

// Keyboard navigation
let currentIndex = -1;
searchBox.addEventListener('keydown', (e) => {
  const items = autocompleteMenu.querySelectorAll('.dropdown-item');
  if (!items.length) return;

  if (e.key === 'ArrowDown') {
    e.preventDefault();
    currentIndex = (currentIndex + 1) % items.length;
  } else if (e.key === 'ArrowUp') {
    e.preventDefault();
    currentIndex = (currentIndex - 1 + items.length) % items.length;
  } else if (e.key === 'Enter') {
    e.preventDefault();
    if (currentIndex >= 0 && currentIndex < items.length) {
      items[currentIndex].click();
    }
  }

  // Update active class
  items.forEach((item, idx) => {
    if (idx === currentIndex) {
      item.classList.add('active');
      item.scrollIntoView({ block: 'nearest' }); // auto scroll
    } else {
      item.classList.remove('active');
    }
  });
});

// Search Quote
const quoteForm = document.querySelector('#quote-form');
const quoteDetails = document.querySelector('#quote-details');

quoteForm.addEventListener('submit', async (evt) => {
  evt.preventDefault();

  const inputValue = searchBox.value;

  console.log('getting quote', inputValue);

  if (inputValue) {
    window.history.pushState({}, '', `?symbol=${inputValue.toUpperCase()}`);
  } else {
    window.history.pushState({}, '', '');
    return;
  }

  quoteDetails.innerHTML = '<div class="spinner-border text-primary mt-5" role="status"></div>';

  const res = await fetch('/quote', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json; charset=UTF-8',
    },
    body: JSON.stringify(inputValue)
  });

  const content = await res.text();

  // console.log(content);
  
  quoteDetails.innerHTML = content;
});
