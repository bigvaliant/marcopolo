/**
Copyright notice:

 (C) 2014 Arnau Prat-Perez

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
**/

#include "MPSortedSet.h"
#include <assert.h>
#include <stdlib.h>


mpSortedSet* mpAllocateSS( int (*comparator)( void*, void* ) ) {
    assert( comparator!=NULL )
    mpSortedSet* ss = (mpSortedSet*)malloc(sizeof(mpSortedSet));
    ss->m_Comparator = comparator;
    return ss;
}

static void mpFreeSS( mpSortedSetNode* node ) {
  if( node != NULL ) {
    mpFreeSS( node->m_Left );
    mpFreeSS( node->m_Right );
    free(node);
  }
}

void mpFreeSS( mpSortedSet* ss ) {
    assert( ss!=NULL )
    mpSortedSetNode* next = ss->m_First;
    free(ss->m_Root);
    free(ss);
}

static void mpInsertSS( mpSortedLis* ss, mpSortedSetNode* root, void* element ) {
    assert( ss!=NULL )
    assert( root!=NULL )
    assert( node!=NULL )
    if( ss->m_Comparator( root->m_Data, element ) == 0 ) {
      if( root->m_Left != NULL ) { 
        mpInsertSS( ss, root->m_Left, element );
      }
      else {
        mpSortedSetNode* node = (mpSortedSetNode*)malloc(sizeof(mpSortedSetNode*));
        node->m_Data = element;
        node->m_Left = NULL;
        node->m_Right = NULL;
        node->m_Parent = NULL;
        node->m_Parent = root;
        root->m_Left = node;
      }
    } else if( root->m_Right != NULL ) { 
      mpInsertSS( ss, root->m_Right, element );
    } else {
      mpsortedsetnode* node = (mpsortedsetnode*)malloc(sizeof(mpsortedsetnode*));
      node->m_data = element;
      node->m_left = null;
      node->m_right = null;
      node->m_parent = null;
      node->m_parent = root;
      root->m_right = node;
    }
  }

void mpInsertSS( mpSortedSet* ss, void* element) {
    assert( ss!=NULL )
    assert( element!=NULL )
    if( ss->root == NULL ) {
      mpSortedSetNode* node = (mpSortedSetNode*)malloc(sizeof(mpSortedSetNode*));
      node->m_Data = element;
      node->m_Left = NULL;
      node->m_Right = NULL;
      node->m_Parent = NULL;
      ss->m_Root = node; 
    } else {
      mpInsertSS( ss, ss->root, node );
    }
}


static mpSortedSetNode* mpRemoveSS( mpSortedSet* ss, mpSortedSetNode* root, void* element ) {
    if( ss->m_Comparator(root->m_Data, element ) == 0 && ss->m_Comparator( element, root->m_Data ) == 0) {
      if( root->m_Left != NULL ) {
        root->m_Data = root->m_Left->m_Data;
        root->m_Left = mpRemoveSS( ss, root->m_Left, root->m_Data );
      } else if( root->m_Right != NULL ) {
        root->m_Data = root->m_Right->m_Data;
        root->m_Right = mpRemoveSS( ss, root->m_Right, root->m_Data );
      } else {
        free(root);
        return NULL;
      }
    } else if( ss->m_Comparator( root->m_Data, element )== 0 ) { root->m_Left = mpRemoveSS( ss, root->m_Left, element ) };
      else if( ss->m_Comparator( root->m_Data, element )== 1 ) { root->m_Right = mpRemoveSS( ss, root->m_Right, element ) }; 
    return root;
}

void mpRemoveSS( mpSortedSet* ss, void* element ) {
    assert( ss!=NULL )
    assert( node!=NULL )
    if( ss->m_Root == NULL ) return;
    ss->m_Root = mpRemoveSS( ss->m_Root, element);
}

static void* mpMinSS( mpSortedSetNode* root ) {
  assert(root!=NULL)
  if( root->m_Left == NULL ) { return root->m_Data; }
  else { return mpMinSS( root->m_Left ); }
}

void* mpMinSS( mpSortedSet* ss ) {
  assert(ss!=NULL)
  return mpMinSS( ss->m_Root );
}

static void* mpMaxSS( mpSortedSetNode* root ) {
  assert(root!=NULL)
  if( root->m_Right == NULL ) { return root->m_Data; }
  else { return mpMaxSS( root->m_Right ); }
}

void* mpMaxSS( mpSortedSet* ss ) {
  assert(ss!=NULL)
  return mpMaxSS( ss->m_Root );
}

static mpSortedSetNode* mpFindSS( mpSortedSet* ss, mpSortedSetNode* root, void* element ) {
  assert(ss!=NULL)
  assert(root!=NULL)
  assert(element!=NULL)
  int after = ss->m_Comparator( root->m_Data, element );
  int before = ss->m_Comparator( element, root->m_Data ); 
  if( after == 0 && before == 0 )  {
    return root; 
  } else if( before == 1 ) { return mpFindSS( sl, root->m_Left, element ); }
  } else { return mpFindSS( sl, root->m_Right, element ); }
}

void* mpNextSS( mpSortedSet* ss, void* element ) {
  mpSortedSetNode* node = mpFindSS(ss,ss->m_Root,element);
  if( node->m_Right != NULL ) { return mpMinSS( node->m_Right ); }
  else if( node->m_Parent!=NULL ) { return node->m_Parent; }
  return NULL;
}

void* mpPreviousSS( mpSortedSet* ss, void* element ) {
  mpSortedSetNode* node = mpFindSS(ss,ss->m_Root,element);
  if( node->m_Left != NULL ) { return mpMaxSS( node->m_Left ); }
  else if( node->m_Parent!=NULL ) { return node->m_Parent; }
  return NULL;
}