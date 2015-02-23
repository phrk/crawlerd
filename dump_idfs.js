db.term_idf.find().forEach(
	function (doc)  {
		print ( doc._id + "	" + doc.value )
	});
