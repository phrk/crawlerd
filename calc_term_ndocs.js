
db.pages.mapReduce(function () {
	
	try {
	
		var words = this.text.split(' ');
		var unique_words = {};
		
		for (var i in words) {
			if (words[i].length > 2 && words[i].length < 23)
				unique_words[ words[i] ] = 1;
		}
		
		for (var word in unique_words)
			emit (word, 1 );
	
	
	} catch (e) {
		
	}
},

function (key, values) {
	
	var ndocs = 0;
	
	try {
	
		for (var i in values)
			ndocs += values [i];
	
	} catch (e) {
		
	}
	
	return ndocs;
},

{
	out : "terms_ndocs"
}

);
