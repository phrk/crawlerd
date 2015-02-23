
// db.pages.count();

db.terms_ndocs.mapReduce(function () {
	
	//try {
		var all_docs_count = 22715.0;
		
		
		//emit(this._id, this.value );
		emit(this._id, Math.log( (all_docs_count - this.value + 0.5 ) / (this.value + 0.5) ) );
	
		//} catch (e) {
		
	//}
},

function (key, values) {

	try {
		for (var i in values)
			return values[i];
	
	} catch (e) {
		
	}
},

{
	out : "term_idf"
}

);

