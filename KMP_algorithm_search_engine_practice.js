var makeKMPTable = function(word) {
    if(Object.prototype.toString.call(word) == '[object String]' ) {
        word = word.split('');
    }
    var results = [];
    var pos = 2;
    var cnd = 0;

    results[0] = -1;
    results[1] = 0;
    while (pos &lt; word.length) {
        if (word[pos - 1] == word[cnd]) {
            cnd++;
            results[pos] = cnd;
            pos++;
        } else if (cnd &gt; 0) {
            cnd = results[cnd];
        } else {
            results[pos] = 0;
            pos++;
        }
    }
    return results;
};

var KMPSearch = function(string, word) {
    if(Object.prototype.toString.call(string) == '[object String]' ) {
        string = string.split('');
    }
    if(Object.prototype.toString.call(word) == '[object String]' ) {
        word = word.split('');
    }

    var index = -1;
    var m = 0;
    var i = 0;
    var T = makeKMPTable(word);

    while (m + i &lt; string.length) {
        if (word[i] == string[m + i]) {
            if (i == word.length - 1) {
                return m;
            }
            i++;
        } else {
            m = m + i - T[i];
            if (T[i] &gt; -1) {
                i = T[i];
            } else {
                i = 0;
            }
        }
    }
    return index;
};