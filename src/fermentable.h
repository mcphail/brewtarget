/*
 * fermentable.h is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
 * - Jeff Bailey <skydvr38@verizon.net>
 * - Kregg K <gigatropolis@yahoo.com>
 * - Mik Firestone <mikfire@gmail.com>
 * - Philip Greggory Lee <rocketman768@gmail.com>
 * - Samuel Östling <MrOstling@gmail.com>
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FERMENTABLE_H
#define _FERMENTABLE_H

#include <QStringList>
#include <QString>
#include "ingredient.h"
#include "unit.h"

// Forward declarations.
class Fermentable;
bool operator<(Fermentable &f1, Fermentable &f2);
bool operator==(Fermentable &f1, Fermentable &f2);

/*!
 * \class Fermentable
 * \author Philip G. Lee
 *
 * \brief Model for a fermentable record in the database.
 */
class Fermentable : public Ingredient
{
   Q_OBJECT
   Q_CLASSINFO("signal", "fermentables")

   friend class Brewtarget;
   friend class BeerXML;
   friend class Database;
   friend class FermentableDialog;
public:

   //! \brief The type of Fermentable.
   enum Type {Grain, Sugar, Extract, Dry_Extract, Adjunct}; // NOTE: BeerXML expects a space for "Dry_Extract". We're screwed.
   //! \brief The addition method.
   enum AdditionMethod {Mashed, Steeped, Not_Mashed};
   //! \brief The addition time.
   enum AdditionTime {Normal, Late};
   Q_ENUMS( Type AdditionMethod AdditionTime )

   virtual ~Fermentable() {}

   //! \brief The \c Type.
   Q_PROPERTY( Type type                     READ type                   WRITE setType                   /*NOTIFY changed*/ /*changedType*/ )
   //! \brief The \c Type string.
   Q_PROPERTY( QString typeString            READ typeString             /*WRITE*/                       /*NOTIFY changed*/ /*changedTypeString*/             STORED false )
   //! \brief The translated \c Type string.
   Q_PROPERTY( QString typeStringTr          READ typeStringTr           /*WRITE*/                       /*NOTIFY changed*/ /*changedTypeStringTr*/           STORED false )
   //! \brief The \c addition method.
   Q_PROPERTY( AdditionMethod additionMethod READ additionMethod         WRITE setAdditionMethod         /*NOTIFY changed*/ /*changedAdditionMethod*/         STORED false )
   //! \brief The translated \c Method string.
   Q_PROPERTY( QString additionMethodStringTr READ additionMethodStringTr /*WRITE*/                      /*NOTIFY changed*/ /*changedAdditionMethodStringTr*/ STORED false )
   //! \brief The \c addition time.
   Q_PROPERTY( AdditionTime additionTime     READ additionTime           WRITE setAdditionTime           /*NOTIFY changed*/ /*changedAdditionTime*/           STORED false )
   //! \brief The translated \c Addition string.
   Q_PROPERTY( QString additionTimeStringTr  READ additionTimeStringTr   /*WRITE*/                       /*NOTIFY changed*/ /*changedAdditionTimeStringTr*/   STORED false )
   //! \brief The amount in kg.
   Q_PROPERTY( double amount_kg              READ amount_kg              WRITE setAmount_kg              /*NOTIFY changed*/ /*changedAmount_kg*/ )
   //! \brief The amount in inventory in kg.
   Q_PROPERTY( double inventory              READ inventory              WRITE setInventoryAmount        /*NOTIFY changed*/ /*changedInventory*/ )
   //! \brief The inventory table id, needed for signals
   Q_PROPERTY( double inventoryId            READ inventoryId            WRITE setInventoryId            /*NOTIFY changed*/ /*changedInventoryId*/ )
   //! \brief The yield (when finely milled) as a percentage of equivalent glucose.
   Q_PROPERTY( double yield_pct              READ yield_pct              WRITE setYield_pct              /*NOTIFY changed*/ /*changedYield_pct*/ )
   //! \brief The color in SRM.
   Q_PROPERTY( double color_srm              READ color_srm              WRITE setColor_srm              /*NOTIFY changed*/ /*changedColor_srm*/ )
   //! \brief Whether to add after the boil.
   Q_PROPERTY( bool addAfterBoil             READ addAfterBoil           WRITE setAddAfterBoil           /*NOTIFY changed*/ /*changedAddAfterBoil*/ )
   //! \brief The origin.
   Q_PROPERTY( QString origin                READ origin                 WRITE setOrigin                 /*NOTIFY changed*/ /*changedOrigin*/ )
   //! \brief The supplier.
   Q_PROPERTY( QString supplier              READ supplier               WRITE setSupplier               /*NOTIFY changed*/ /*changedSupplier*/ )
   //! \brief The notes.
   Q_PROPERTY( QString notes                 READ notes                  WRITE setNotes                  /*NOTIFY changed*/ /*changedNotes*/ )
   //! \brief The difference in yield between coarsely milled and finely milled grain.
   Q_PROPERTY( double coarseFineDiff_pct     READ coarseFineDiff_pct     WRITE setCoarseFineDiff_pct     /*NOTIFY changed*/ /*changedCoarseFineDiff_pct*/ )
   //! \brief The moisture in pct.
   Q_PROPERTY( double moisture_pct           READ moisture_pct           WRITE setMoisture_pct           /*NOTIFY changed*/ /*changedMoisture_pct*/ )
   //! \brief The diastatic power in Lintner.
   Q_PROPERTY( double diastaticPower_lintner READ diastaticPower_lintner WRITE setDiastaticPower_lintner /*NOTIFY changed*/ /*changedDiastaticPower_lintner*/ )
   //! \brief The percent protein.
   Q_PROPERTY( double protein_pct            READ protein_pct            WRITE setProtein_pct            /*NOTIFY changed*/ /*changedProtein_pct*/ )
   //! \brief The maximum recommended amount in a batch, as a percentage of the total grains.
   Q_PROPERTY( double maxInBatch_pct         READ maxInBatch_pct         WRITE setMaxInBatch_pct         /*NOTIFY changed*/ /*changedMaxInBatch_pct*/ )
   //! \brief Whether a mash is recommended.
   Q_PROPERTY( bool recommendMash            READ recommendMash          WRITE setRecommendMash          /*NOTIFY changed*/ /*changedRecommendMash*/ )
   //! \brief The IBUs per gal/lb if this is a liquid extract.
   Q_PROPERTY( double ibuGalPerLb            READ ibuGalPerLb            WRITE setIbuGalPerLb            /*NOTIFY changed*/ /*changedIbuGalPerLb*/ )
   //! \brief The maximum kg of equivalent glucose that will come from this Fermentable.
   Q_PROPERTY( double equivSucrose_kg        READ equivSucrose_kg        /*WRITE*/                       /*NOTIFY changed*/ /*changedEquivSucrose_kg*/        STORED false )
   //! \brief Whether the grains actually is mashed.
   Q_PROPERTY( bool isMashed                 READ isMashed               WRITE setIsMashed               /*NOTIFY changed*/ /*changedIsMashed*/ )
   //! \brief Whether this fermentable is an extract.
   Q_PROPERTY( bool isExtract                READ isExtract STORED false)
   //! \brief Whether this fermentable is a sugar. Somewhat redundant, but it makes for nice symetry elsewhere
   Q_PROPERTY( bool isSugar                  READ isSugar STORED false)

   Type type() const;
   double amount_kg() const;
   double inventory();
   int inventoryId();
   double yield_pct() const;
   double color_srm() const;
   bool addAfterBoil() const;
   const QString origin() const;
   const QString supplier() const;
   const QString notes() const;
   double coarseFineDiff_pct() const;
   double moisture_pct() const;
   double diastaticPower_lintner() const;
   double protein_pct() const;
   double maxInBatch_pct() const;
   bool recommendMash() const;
   double ibuGalPerLb() const;
   bool isMashed() const;

   const QString typeString() const;
   //! Returns a translated type string.
   const QString typeStringTr() const;
   AdditionMethod additionMethod() const;
   //! Returns a translated addition method string.
   const QString additionMethodStringTr() const;
   AdditionTime additionTime() const;
   //! Returns a translated addition time string.
   const QString additionTimeStringTr() const;
   // Calculated getters.
   double equivSucrose_kg() const;
   bool isExtract() const;
   bool isSugar() const;
   bool cacheOnly() const;


   void setType( Type t );
   void setAdditionMethod( AdditionMethod m );
   void setAdditionTime( AdditionTime t );
   void setAmount_kg( double num );
   void setInventoryAmount( double num );
   void setYield_pct( double num );
   void setColor_srm( double num );
   void setAddAfterBoil( bool b );
   void setOrigin( const QString& str );
   void setSupplier( const QString& str);
   void setNotes( const QString& str );
   void setCoarseFineDiff_pct( double num );
   void setMoisture_pct( double num );
   void setDiastaticPower_lintner( double num );
   void setProtein_pct( double num );
   void setMaxInBatch_pct( double num );
   void setRecommendMash( bool b );
   void setIbuGalPerLb( double num );
   void setIsMashed(bool var );
   void setCacheOnly(bool cache );
   void setInventoryId(int key);

   void save();

   static QString classNameStr();

signals:

private:
   Fermentable(Brewtarget::DBTable table, int key);
   Fermentable(Brewtarget::DBTable table, int key, QSqlRecord rec);
   Fermentable( Fermentable &other );
   Fermentable( QString name, bool cache = true );

   static bool isValidType( const QString& str );
   static QStringList types;

   static QHash<QString,QString> tagToProp;
   static QHash<QString,QString> tagToPropHash();

   QString m_typeStr;
   Type m_type;
   double m_amountKg;
   double m_yieldPct;
   double m_colorSrm;
   bool m_isAfterBoil;
   QString m_origin;
   QString m_supplier;
   QString m_notes;
   double m_coarseFineDiff;
   double m_moisturePct;
   double m_diastaticPower;
   double m_proteinPct;
   double m_maxInBatchPct;
   bool m_recommendMash;
   double m_ibuGalPerLb;
   double m_inventory;
   int m_inventory_id;
   bool m_isMashed;
   bool m_cacheOnly;
};

Q_DECLARE_METATYPE( QList<Fermentable*> )

inline bool FermentablePtrLt( Fermentable* lhs, Fermentable* rhs)
{
   return *lhs < *rhs;
}

inline bool FermentablePtrEq( Fermentable* lhs, Fermentable* rhs)
{
   return *lhs == *rhs;
}

inline bool fermentablesLessThanByWeight(const Fermentable* lhs, const Fermentable* rhs)
{
   // Sort by name if the two fermentables are of equal weight
   if ( qFuzzyCompare(lhs->amount_kg(), rhs->amount_kg() ) )
      return lhs->name() < rhs->name();

   // Yes. I know. This seems silly, but I want the returned list in
   // descending not ascending order.
   return lhs->amount_kg() > rhs->amount_kg();
}

struct Fermentable_ptr_cmp
{
   bool operator()( Fermentable* lhs, Fermentable* rhs)
   {
      return *lhs < *rhs;
   }
};

struct Fermentable_ptr_equals
{
   bool operator()( Fermentable* lhs, Fermentable* rhs )
   {
      return *lhs == *rhs;
   }
};

#endif
