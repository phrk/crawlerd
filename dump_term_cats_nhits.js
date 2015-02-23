db.term_cats_nhits.find().forEach(
	function (doc)  {
		
		var ret = doc._id + "	";
		
		for (var cat in doc.value) {
			
			ret += cat + ":" + doc.value[cat] + "	";
		}
		
		print ( ret );
	});
