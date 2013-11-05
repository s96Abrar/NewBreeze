/*
	*
	* NBCatalogDelegate.hpp - NBCatalogDelegate.cpp Header
	*
*/

#ifndef NBCATALOGDELEGATE_HPP
#define NBCATALOGDELEGATE_HPP

#include <Global.hpp>

class NBCatalogDelegate : public QItemDelegate {
    Q_OBJECT

	public:
		void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
		QSize sizeHint( const QStyleOptionViewItem &, const QModelIndex & ) const;
};

#endif
