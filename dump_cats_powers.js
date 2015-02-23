db.cats_powers.find().forEach(
	function (doc) {
		print ( doc._id + "	" + doc.value )
	}
);